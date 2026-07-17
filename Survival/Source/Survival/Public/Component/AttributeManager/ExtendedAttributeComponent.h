// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtendedAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, InValue);


UENUM(BlueprintType)
enum class EAttributeTypes : uint8
{
	Health,
	Food,
	Hydration
};



UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtendedAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtendedAttributeComponent();



	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnCurrentFoodChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnCurrentHydrationChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnMaxFoodChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnMaxHydrationChanged;



	/*
	* Getter함수
	*/
	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetCurrentFood() const { return CurrentFood; }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetCurrentHydration() const { return CurrentHydration; }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetMaxFood() const { return MaxFood; }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetMaxHydration() const { return MaxHydration; }

	/*
	* Setter 함수
	*/

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetMaxHealth(float InHealth);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetMaxFood(float InFood);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetMaxHydration(float InHydration);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetCurrentHealth(float InHealth);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetCurrentFood(float InFood);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetCurrentHydration(float InHydration);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float HydrationConsumeRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float FoodZeroDamage = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribuet", meta = (AllowPrivateAccess = "true"))
	float HydrationZeroDamage = 5.f;
		
};
