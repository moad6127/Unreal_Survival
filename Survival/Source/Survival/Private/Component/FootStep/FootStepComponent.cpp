// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FootStep/FootStepComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicsEngine/PhysicsSettings.h"



void UFootStepComponent::Execute_FootStep_Logic(USkeletalMeshComponent* MeshComp, bool IsRightFoot)
{
	TEnumAsByte<EPhysicalSurface> FootStepSurfaceType;
	FVector HitLocation;
	bool bSuccess;

	SurfaceTypeDetection(MeshComp, IsRightFoot, FootStepSurfaceType, HitLocation, bSuccess);
	if (bSuccess)
	{
		FName Name = GetSurfaceName(FootStepSurfaceType);
		FString DisplayName = Name.IsNone() ? UEnum::GetValueAsString(FootStepSurfaceType.GetValue()): Name.ToString();
		UE_LOG(LogTemp, Warning, TEXT("Surface Type: %s"), *DisplayName);
		PlayFootStepSound(FootStepSurfaceType, HitLocation);
		//TODO : 파티클 이펙트 
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
	if (HitResult.PhysMaterial.IsValid())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("%s"),
			*HitResult.PhysMaterial->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("No Physical Material"));
	}
}

FVector UFootStepComponent::GetNotifySocketLocation(USkeletalMeshComponent* MeshComp, bool IsRightFoot)
{
	FName SocketName = IsRightFoot ? FName("foot_r") : FName("foot_l");
	return MeshComp->GetSocketLocation(SocketName);;
}

void UFootStepComponent::PlayFootStepSound(const TEnumAsByte<EPhysicalSurface>& SurfaceType, const FVector& Location)
{
	USoundBase**  SurfaceSound = FootStepSoundMap.Find(SurfaceType);
	if (*SurfaceSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetOwner(), *SurfaceSound, Location);
	}
}

FName UFootStepComponent::GetSurfaceName(TEnumAsByte<EPhysicalSurface> SurfaceType)
{
	const UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get();
	for (const FPhysicalSurfaceName& SurfaceName : PhysicsSettings->PhysicalSurfaces)
	{
		if (SurfaceName.Type == SurfaceType.GetValue())
		{
			return SurfaceName.Name;
		}
	}
	return NAME_None;
}
