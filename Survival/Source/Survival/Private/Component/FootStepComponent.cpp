// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FootStepComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "PhysicalMaterials/PhysicalMaterial.h"


void UFootStepComponent::Execute_FootStep_Logic(USkeletalMeshComponent* MeshComp, bool IsRightFoot)
{
	TEnumAsByte<EPhysicalSurface> FootStepSurfaceType;
	FVector HitLocation;
	bool bSuccess;

	SurfaceTypeDetection(MeshComp, IsRightFoot, FootStepSurfaceType, HitLocation, bSuccess);
	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Surface Type: %s"), *UEnum::GetValueAsString(FootStepSurfaceType.GetValue()));
	}
}

void UFootStepComponent::SurfaceTypeDetection(USkeletalMeshComponent* MeshComp, bool IsRightFoot, TEnumAsByte<EPhysicalSurface>& OutSurfaceType, FVector& OutLocation, bool& bOutSuccess)
{
	FVector FootLocationStart = GetNotifySocketLocation(MeshComp, IsRightFoot);
	FVector FootLoationEnd = FootLocationStart - FVector(0, 0, 50);
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = true;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		FootLocationStart,
		FootLoationEnd,
		ECollisionChannel::ECC_Visibility,
		QueryParams);
	if (bHit)
	{
		OutSurfaceType = UGameplayStatics::GetSurfaceType(HitResult);
		OutLocation = HitResult.Location;
		bOutSuccess = true;
	}
	else
	{
		OutSurfaceType = SurfaceType_Default;
		OutLocation = FVector::ZeroVector;
		bOutSuccess = false;
	}
}

FVector UFootStepComponent::GetNotifySocketLocation(USkeletalMeshComponent* MeshComp, bool IsRightFoot)
{
	FName SocketName = IsRightFoot ? FName("foot_r") : FName("foot_l");
	return MeshComp->GetSocketLocation(SocketName);;
}
