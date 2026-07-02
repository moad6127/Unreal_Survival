// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ExtenedFootStepComponent.h"
#include "FootStepComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UFootStepComponent : public UExtenedFootStepComponent
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void Execute_FootStep_Logic(USkeletalMeshComponent* MeshComp, bool IsRightFoot) override;

private:
	void SurfaceTypeDetection(USkeletalMeshComponent* MeshComp, bool IsRightFoot, TEnumAsByte<EPhysicalSurface>& OutSurfaceType, FVector& OutLocation, bool& bOutSuccess);
	FVector GetNotifySocketLocation(USkeletalMeshComponent* MeshComp, bool IsRightFoot);
};
