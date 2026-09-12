// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AnimalIdleAnimService.generated.h"

/**
 * 
 */

struct FBTAnimalIdleMemory
{
	float TimeUntilNextAction = 0.f;
};


UCLASS()
class SURVIVAL_API UAnimalIdleAnimService : public UBTService
{
	GENERATED_BODY()
	
public:
	UAnimalIdleAnimService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FBTAnimalIdleMemory); }

private:
	void PickNextIdleAction(class AAnimalCharacter* Animal) const;

	UPROPERTY(EditAnywhere, Category = "Idle")
	float MinIdleDuration = 5.f;

	UPROPERTY(EditAnywhere, Category = "Idle")
	float MaxIdleDuration = 15.f;
};
