// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"


class UPawnSensingComponent;
class UAttributeComponent;
class UReplicationComponent;
class URagdollComponent;
class UMotionWarpingComponent;


UENUM(BlueprintType)
enum class EAnimalIdleAction : uint8
{
	Breathe,
	LookAround,
	Lying,
	Howling
};

USTRUCT(BlueprintType)
struct FAnimalIdleActionWeight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAnimalIdleAction Action = EAnimalIdleAction::LookAround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 1.f;
};

UCLASS()
class SURVIVAL_API AAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimalCharacter();

	UFUNCTION(BlueprintCallable, Category = "Animal|State")
	void SetIdleAction(EAnimalIdleAction NewAction);

	UFUNCTION(BlueprintPure, Category = "Animal|State")
	EAnimalIdleAction GetIdleAction() const { return CurrentIdleAction; }

	UFUNCTION(BlueprintCallable, Category = "Animal|AI")
	void SetReadyToMove(bool bReady);

	UFUNCTION(BlueprintPure, Category = "Animal|AI")
	bool IsReadyToMove() const { return bIsReadyToMove; }

	UFUNCTION(BlueprintCallable, Category = "Animal|AI")
	void RequestEndIdle() { bWantsToEndIdle = true; }

	UFUNCTION(BlueprintCallable, Category = "Animal|AI")
	void ClearEndIdleRequest() { bWantsToEndIdle = false; }

	UFUNCTION(BlueprintCallable, Category = "Animal|Combat")
	void FaceTarget(AActor* Target);

	UFUNCTION(BlueprintPure, Category = "Animal|AI")
	bool WantsToEndIdle() const { return bWantsToEndIdle; }

	void SetAlertMovementSpeed();

	// 동물별로 다르게 설정하는 가중치 목록
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animal|State")
	TArray<FAnimalIdleActionWeight> AvailableIdleActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Combat")
	float DamageAmount = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Animal|AI")
	float WanderDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float BaseWalkSpeed = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animal|Movement")
	float AlertWalkSpeed = 750.f;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	UFUNCTION()
	void HandleDeath();

	UFUNCTION()
	void HandleAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	UPROPERTY(BlueprintReadOnly, Category = "Animal|AI")
	bool bIsReadyToMove = true;

	UPROPERTY(BlueprintReadOnly, Category = "Animal|AI")
	bool bWantsToEndIdle = false;

	UPROPERTY(EditDefaultsOnly, Category = "Animal|Movement")
	float TurnInterpSpeed = 2.5f;  // 낮을수록 더 느긋하게 돎


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Components")
	TObjectPtr<UAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Components")
	TObjectPtr<UReplicationComponent> ReplicationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Components")
	TObjectPtr<URagdollComponent> RagdollComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal|Components")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;


	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Animal|State")
	EAnimalIdleAction CurrentIdleAction = EAnimalIdleAction::Breathe;
};
