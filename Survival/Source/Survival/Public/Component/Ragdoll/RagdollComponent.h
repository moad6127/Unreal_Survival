// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Ragdoll/ExtenedRagdollComponent.h"
#include "RagdollComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API URagdollComponent : public UExtenedRagdollComponent
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;
	virtual void OnRep_bRagdolling() override;
	virtual void ToRagdoll() override;

	UFUNCTION()
	void HandleOnDeath();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ragdoll")
	FName RagdollBoneName = TEXT("pelvis");
};
