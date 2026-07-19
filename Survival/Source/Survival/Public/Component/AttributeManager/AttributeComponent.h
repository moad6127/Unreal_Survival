// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/AttributeManager/ExtendedAttributeComponent.h"
#include "AttributeComponent.generated.h"

/**
 * 
 */

UCLASS()
class SURVIVAL_API UAttributeComponent : public UExtendedAttributeComponent
{
	GENERATED_BODY()
	
public:


protected:

	virtual void BeginPlay() override;

private:
	void InitValues();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyStatDamage();

	void StartStatConsumeTimer();

	void HandleStatConsumeTick();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float StatConsumeRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float FoodConsumeDamage = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float HydrationConsumeDamage = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float FoodZeroDamage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float HydrationZeroDamage = 1.f;

	FTimerHandle StatConsumeTimer;
};
