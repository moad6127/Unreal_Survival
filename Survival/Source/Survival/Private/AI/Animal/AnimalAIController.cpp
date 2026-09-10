// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animal/AnimalAIController.h"
#include "BehaviorTree/BehaviorTree.h"

void AAnimalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
