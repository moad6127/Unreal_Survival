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
	/*
	* AnimNotify에서 실행되는 로직이다
	*/
	virtual void Execute_FootStep_Logic(USkeletalMeshComponent* MeshComp, bool IsRightFoot) override;

private:
	/*
	* 라인트래이스를 사용해서 현재 Surface타입과 위치를 알아내기
	*/
	void SurfaceTypeDetection(USkeletalMeshComponent* MeshComp, bool IsRightFoot, TEnumAsByte<EPhysicalSurface>& OutSurfaceType, FVector& OutLocation, bool& bOutSuccess);
	/*
	* Socket의 위치 알아내기
	*/
	FVector GetNotifySocketLocation(USkeletalMeshComponent* MeshComp, bool IsRightFoot);
	void PlayFootStepSound(const TEnumAsByte<EPhysicalSurface>& SurfaceType, const FVector& Location);

	UPROPERTY(EditDefaultsOnly, Category = "FootStep")
	TMap<TEnumAsByte<EPhysicalSurface>, USoundBase*> FootStepSoundMap;
};
