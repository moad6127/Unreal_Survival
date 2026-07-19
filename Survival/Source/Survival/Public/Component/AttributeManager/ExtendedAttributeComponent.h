// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtendedAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, InValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);



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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ModifyAttribute(EAttributeTypes AttributeType, float Amount);




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

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnDeath OnDeath;


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

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(Server, Reliable)
	void Server_ApplyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_CurrentHealth();

	UFUNCTION()
	void OnRep_CurrentFood();

	UFUNCTION()
	void OnRep_CurrentHydration();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxFood = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxHydration = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 50.f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentFood, EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float CurrentFood = 50.f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHydration, EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float CurrentHydration = 50.f;

	bool bIsDead = false;
};
