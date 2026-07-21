// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerStart/RespawnLocation.h"
#include "Components/CapsuleComponent.h"

FTransform ARespawnLocation::GetRespawnTransform() const
{
	FTransform Transform = GetCapsuleComponent()->GetComponentTransform();
	Transform.SetScale3D(FVector::OneVector);
	return Transform;
}
