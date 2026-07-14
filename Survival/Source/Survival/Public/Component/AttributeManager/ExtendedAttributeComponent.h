// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtendedAttributeComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtendedAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtendedAttributeComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float MaxFood = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float MaxHydration = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float CurrentFood = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float CurrentHydration = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float FoodConsumeRate = 0.1f;
	
	float HydrationConsumeRate = 0.1f;
		
};
