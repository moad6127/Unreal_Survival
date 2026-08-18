// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/CombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombatComponent::TryMeleeDamage()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	const FVector BoxCenter = Owner->GetActorLocation() + Owner->GetActorForwardVector() * ForwardOffset;
	const FQuat BoxRotation = Owner->GetActorQuat();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	TArray<AActor*> OverlappedActors;

	UKismetSystemLibrary::BoxOverlapActors(
		Owner,
		BoxCenter,
		BoxExtent,
		TArray<TEnumAsByte<EObjectTypeQuery>>{ UEngineTypes::ConvertToObjectType(ECC_Pawn) },
		nullptr,
		ActorsToIgnore,
		OverlappedActors
	);

	for (AActor* HitActor : OverlappedActors)
	{
		UE_LOG(LogTemp, Log, TEXT("Combat: Melee box hit %s"), *HitActor->GetName());
	}
}
