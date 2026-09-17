// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimalAIController.generated.h"

/**
 * 
 */
class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;


UCLASS()
class SURVIVAL_API AAnimalAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAnimalAIController();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void NotifyThreatDetected(APawn* NewThreat);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ResetChaseLeash();
protected:
	virtual void OnPossess(APawn* InPawn) override;

	void InitializeBlackboardValues();

	UFUNCTION()
	void HandlePerceptionUpdated(AActor* PerceivedActor, struct FAIStimulus Stimulus);


	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
};
