// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/ChaseLeashService.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Animal/AnimalCharacter.h"
#include "Component/AttributeManager/AttributeComponent.h"
#include "Utils/SurvivalStatics.h"

UChaseLeashService::UChaseLeashService()
{
	NodeName = TEXT("Chase Leash");
}

void UChaseLeashService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	AAnimalCharacter* Animal = AIController ? Cast<AAnimalCharacter>(AIController->GetPawn()) : nullptr;

	if (!BlackboardComp || !Animal)
	{
		return;
	}

	//추격을 시작한 위치와 시간을 알기
	const FVector ChaseOrigin = BlackboardComp->GetValueAsVector(TEXT("ChaseOriginLocation"));
	const float ChaseStartTime = BlackboardComp->GetValueAsFloat(TEXT("ChaseStartTime"));
	const float CurrentTime = Animal->GetWorld()->GetTimeSeconds();

	//시작위치와 시간들의 차이를 구하기
	const float DistanceFromOrigin = FVector::Dist(Animal->GetActorLocation(), ChaseOrigin);
	const float ElapsedTime = CurrentTime - ChaseStartTime;

	bool bShouldEndChase = false;
	if (DistanceFromOrigin > LeashDistance || ElapsedTime > MaxChaseDuration)
	{
		bShouldEndChase = true;
	}

	if (!bShouldEndChase)
	{
		if (AActor* ThreatPawn = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("ThreatPawn"))))
		{
			if (UExtendedAttributeComponent* Attribute = USurvivalStatics::GetComponentFromActor<UExtendedAttributeComponent>(ThreatPawn))
			{
				if (Attribute->IsDead())
				{
					bShouldEndChase = true;
				}
			}
		}
	}

	//정해진 범위를 넘어가면 추격 종료하기
	if (bShouldEndChase)
	{
		BlackboardComp->ClearValue(TEXT("ThreatPawn"));
		BlackboardComp->SetValueAsBool(TEXT("IsReturningToOrigin"), true);

		if (UCharacterMovementComponent* Movement = Animal->GetCharacterMovement())
		{
			Movement->MaxWalkSpeed = Animal->BaseWalkSpeed;
		}
	}
}
