// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/InventoryComponent.h"
#include "Utils/InventoryStatics.h"
#include "Actors/InteractionActor/PickupItem.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->HasAuthority())
	{
		InitInventory();
	}
}

bool UInventoryComponent::FindEmptySlot(const TArray<FInventoryItemSlot>& TargetInventory, int32& OutIndex)
{
	for (int32 Index = 0; Index < TargetInventory.Num(); Index++)
	{
		if (UInventoryStatics::IsItemEmpty(TargetInventory[Index], EmptySlotItem))
		{
			OutIndex = Index;
			return true;
		}
	}
	return false;
}

void UInventoryComponent::AddItemToSlotByIndex(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd, int32 Index)
{
	TargetInventory[Index] = ItemToAdd;
	OnInventorySlotUpdated.Broadcast(Index, ItemToAdd);
}

void UInventoryComponent::DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index)
{
	if (!TargetInventory.IsValidIndex(Index))
	{
		return;
	}
	const FInventoryItemSlot ItemToDrop = TargetInventory[Index];
	SpawnItem(ItemToDrop);
	SetInventorySlotToEmptyByIndex(TargetInventory, Index);
}

void UInventoryComponent::TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd)
{
	int32 EmptyIndex = 0;
	if (FindEmptySlot(TargetInventory, EmptyIndex))
	{
		AddItemToSlotByIndex(TargetInventory, ItemToAdd, EmptyIndex);
	}
	else
	{
		SpawnItem(ItemToAdd);
	}
}

void UInventoryComponent::SpawnItem(const FInventoryItemSlot& ItemToSpawn)
{
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	if (!PickupItemClass || !World || !Owner)
	{
		return;
	}

	FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 10.f;
	SpawnLocation.Z += 50.f;
	const FTransform SpawnTransform(Owner->GetActorRotation(), SpawnLocation, FVector::OneVector);
	APickupItem* SpawnedItem = World->SpawnActorDeferred<APickupItem>(PickupItemClass, SpawnTransform);
	if (SpawnedItem)
	{
		SpawnedItem->SetInventoryItemSlot(ItemToSpawn);
		SpawnedItem->SetSimulatePhysics(true);
		SpawnedItem->FinishSpawning(SpawnTransform);
	}
}

void UInventoryComponent::ConsumeItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index)
{
	if (!TargetInventory.IsValidIndex(Index))
	{
		return;
	}
	const FInventoryItemSlot ConsumedSlot = TargetInventory[Index];
	SetInventorySlotToEmptyByIndex(TargetInventory, Index);

	OnItemConsumed.Broadcast(ConsumedSlot);
}

void UInventoryComponent::InitInventory()
{
	int32 InitInventoryNum = InventorySlots.Num();
	for (int32 Index = 0; Index < DefaultInventorySlotAmount - InitInventoryNum; Index++)
	{
		CreateEmptySlot(InventorySlots);
	}
}

int32 UInventoryComponent::CreateEmptySlot(TArray<FInventoryItemSlot>& TargetInventory)
{
	FInventoryItemSlot EmptySlot;
	EmptySlot.Item = EmptySlotItem;
	return TargetInventory.Add(EmptySlot);
}
