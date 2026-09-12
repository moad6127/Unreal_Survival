// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/AnimalIdleAnimService.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "AI/Animal/AnimalCharacter.h"

UAnimalIdleAnimService::UAnimalIdleAnimService()
{
	NodeName = TEXT("Animal Idle Animation");
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;

}

void UAnimalIdleAnimService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FBTAnimalIdleMemory* Memory = reinterpret_cast<FBTAnimalIdleMemory*>(NodeMemory);
	Memory->TimeUntilNextAction -= DeltaSeconds;

	if (Memory->TimeUntilNextAction > 0.f)
	{
		return;
	}

	AAnimalCharacter* Animal = OwnerComp.GetAIOwner() ? Cast<AAnimalCharacter>(OwnerComp.GetAIOwner()->GetPawn()) : nullptr;
	if (!Animal)
	{
		return;
	}

	PickNextIdleAction(Animal);
	Memory->TimeUntilNextAction = FMath::FRandRange(MinIdleDuration, MaxIdleDuration);
}

void UAnimalIdleAnimService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	// 브랜치가 중단될 때(위협 감지 등) 엎드린 채로 다른 행동을 시작하지 않도록 기본 상태로 되돌림
	if (AAnimalCharacter* Animal = OwnerComp.GetAIOwner() ? Cast<AAnimalCharacter>(OwnerComp.GetAIOwner()->GetPawn()) : nullptr)
	{
		Animal->SetIdleAction(EAnimalIdleAction::Breathe);
	}
}

void UAnimalIdleAnimService::PickNextIdleAction(AAnimalCharacter* Animal) const
{
	const TArray<FAnimalIdleActionWeight>& Options = Animal->AvailableIdleActions;
	if (Options.Num() == 0)
	{
		return;
	}

	float TotalWeight = 0.f;
	for (const FAnimalIdleActionWeight& Option : Options)
	{
		TotalWeight += Option.Weight;
	}

	float Roll = FMath::FRandRange(0.f, TotalWeight);
	for (const FAnimalIdleActionWeight& Option : Options)
	{
		Roll -= Option.Weight;
		if (Roll <= 0.f)
		{
			Animal->SetIdleAction(Option.Action);
			return;
		}
	}
}
