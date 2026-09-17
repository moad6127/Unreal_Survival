// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ChaseLeashService.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UChaseLeashService : public UBTService
{
	GENERATED_BODY()
	
public:
	UChaseLeashService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Chase")
	float LeashDistance = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Chase")
	float MaxChaseDuration = 45.f;
};
