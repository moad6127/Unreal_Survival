// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animal/AnimalAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/Animal/AnimalCharacter.h"

AAnimalAIController::AAnimalAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 3000.f;
	SightConfig->LoseSightRadius = 3300.f;
	SightConfig->PeripheralVisionAngleDegrees = 65.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAnimalAIController::HandlePerceptionUpdated);


}


void AAnimalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	InitializeBlackboardValues();
}

void AAnimalAIController::InitializeBlackboardValues()
{
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(GetPawn());
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

	if (!Animal || !BlackboardComp)
	{
		return;
	}

	BlackboardComp->SetValueAsFloat(TEXT("WanderDistance"), Animal->WanderDistance);

	if (UCharacterMovementComponent* Movement = Animal->GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = Animal->BaseWalkSpeed;
	}
}

void AAnimalAIController::HandlePerceptionUpdated(AActor* PerceivedActor, FAIStimulus Stimulus)
{
	if (!Stimulus.WasSuccessfullySensed())
	{
		return;
	}

	if (APawn* SeenPawn = Cast<APawn>(PerceivedActor))
	{
		NotifyThreatDetected(SeenPawn);
	}
}


void AAnimalAIController::NotifyThreatDetected(APawn* NewThreat)
{
	if (!NewThreat)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	// 이미 위협이 지정돼 있으면 덮어쓰지 않음 (lecture와 동일한 의도)
	if (BlackboardComp->GetValueAsObject(TEXT("ThreatPawn")))
	{
		return;
	}

	BlackboardComp->SetValueAsObject(TEXT("ThreatPawn"), NewThreat);

	if (AAnimalCharacter* Animal = Cast<AAnimalCharacter>(GetPawn()))
	{
		Animal->SetAlertMovementSpeed();
	}
}

