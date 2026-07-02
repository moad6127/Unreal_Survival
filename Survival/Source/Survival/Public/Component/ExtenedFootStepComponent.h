// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedFootStepComponent.generated.h"


class USkeletalMeshComponent;

UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedFootStepComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedFootStepComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "FootStep")	
	virtual void Execute_FootStep_Logic(USkeletalMeshComponent* MeshComp,bool IsRightFoot);
};
