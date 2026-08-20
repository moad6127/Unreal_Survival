// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/CombatComponent.h"
#include "Component/Equipment/ExtenedEquipmentComponent.h"
#include "Utils/SurvivalStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UCombatComponent::TryMeleeDamage()
{
	ACharacter* OwningCharacter = USurvivalStatics::GetCharacterFromComponent(this);
	if (!OwningCharacter)
	{
		return;
	}
	const FVector ForwardVector = OwningCharacter->GetActorForwardVector();
	const FVector StartPosition = OwningCharacter->GetActorLocation() + ForwardVector * ForwardOffset;
	const FVector EndPosition = StartPosition + ForwardVector * TraceRange;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwningCharacter);

	TArray<FHitResult> LocalHits;
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		this,
		StartPosition,
		EndPosition,
		BoxHalfSize,
		OwningCharacter->GetActorRotation(),
		DamageObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		LocalHits,
		true);

	ProcessHits(LocalHits);
}

void UCombatComponent::ProcessHits(const TArray<FHitResult>& Hits)
{
	// 같은 액터에 여러 번 데미지가 들어가는 것을 막기 위한 중복 체크용
	TArray<AActor*> LocalHitActors;

	for (const FHitResult& LocalHit : Hits)
	{
		if (!LocalHit.bBlockingHit)
		{
			continue;
		}

		AActor* HitActor = LocalHit.GetActor();
		if (!HitActor || LocalHitActors.Contains(HitActor))
		{
			continue;
		}
		LocalHitActors.Add(HitActor);

		ApplyDamageToActor(HitActor, LocalHit);
	}
}

void UCombatComponent::ApplyDamageToActor(AActor* TargetActor, const FHitResult& Hit)
{
	UExtenedEquipmentComponent* EquipmentComp = USurvivalStatics::GetComponentFromComponent<UExtenedEquipmentComponent>(this);
	if (!EquipmentComp)
	{
		return;
	}

	const FInventoryItemSlot EquippedSlot = EquipmentComp->GetEquipmentSlot();
	const FItem* EquippedItem = EquippedSlot.Item.GetRow<FItem>(TEXT("UCombatComponent::ApplyDamageToActor"));
	if (!EquippedItem)
	{
		return;
	}

	if (EquippedItem->AssignedAttribute.AttributeType != EAttributeTypes::Damage)
	{
		UE_LOG(LogTemp, Warning, TEXT("CombatComponent: %s has no Damage attribute assigned in its data table row."), *EquippedSlot.Item.RowName.ToString());
		return;
	}

	const float DamageAmount = EquippedItem->AssignedAttribute.Amount;
	AController* InstigatorController = USurvivalStatics::GetControllerFromComponent(this);

	UGameplayStatics::ApplyPointDamage(
		TargetActor,
		DamageAmount,
		Hit.ImpactNormal * -1.f,
		Hit,
		InstigatorController,
		GetOwner(),
		nullptr);
}
