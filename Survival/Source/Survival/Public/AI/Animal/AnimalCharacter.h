// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

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

	// 동물별로 다르게 설정하는 가중치 목록
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animal|State")
	TArray<FAnimalIdleActionWeight> AvailableIdleActions;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Animal|State")
	EAnimalIdleAction CurrentIdleAction = EAnimalIdleAction::Breathe;
};
