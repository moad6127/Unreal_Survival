// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/LootDrop/LootDropComponent.h"
#include "Component/AttributeManager/ExtendedAttributeComponent.h"
#include "Utils/SurvivalStatics.h"
#include "Actors/InteractionActor/PickupItem.h"


ULootDropComponent::ULootDropComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULootDropComponent::BeginPlay()
{
	Super::BeginPlay();
	if (UExtendedAttributeComponent* Attribute = USurvivalStatics::GetComponentFromActor<UExtendedAttributeComponent>(GetOwner()))
	{
		Attribute->OnDeath.AddDynamic(this, &ULootDropComponent::HandleOnDeath);
	}
}

void ULootDropComponent::SpawnLootItem(const FLootDropEntry& Entry)
{
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	if (!PickupItemClass || !World || !Owner)
	{
		return;
	}

	FInventoryItemSlot ItemSlot;
	ItemSlot.Item = Entry.Item;
	ItemSlot.Amount = 1; /* 나중에 스택으로 할경우 해당기능으로FMath::RandRange(Entry.MinQuantity, Entry.MaxQuantity);*/

	FVector SpawnLocation = Owner->GetActorLocation() + FVector(FMath::FRandRange(-30.f, 30.f), FMath::FRandRange(-30.f, 30.f), 0.f);
	SpawnLocation.Z += 50.f;
	const FTransform SpawnTransform(Owner->GetActorRotation(), SpawnLocation, FVector::OneVector);

	APickupItem* SpawnedItem = World->SpawnActorDeferred<APickupItem>(PickupItemClass, SpawnTransform);
	if (SpawnedItem)
	{
		SpawnedItem->SetInventoryItemSlot(ItemSlot);
		SpawnedItem->SetSimulatePhysics(true);
		SpawnedItem->FinishSpawning(SpawnTransform);
	}
}

void ULootDropComponent::HandleOnDeath()
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority() || bHasDroppedLoot)
	{
		return;
	}
	bHasDroppedLoot = true;

	for (const FLootDropEntry& Entry : LootTable)
	{
		if (!Entry.Item.DataTable || FMath::FRand() > Entry.DropChance)
		{
			continue;
		}

		SpawnLootItem(Entry);
	}
}