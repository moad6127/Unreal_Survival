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

bool UInventoryComponent::CanArrayOfItemsBeFoundInInventory(const TArray<FInventoryItemSlot>& ItemsToFind) const
{
	for (const FInventoryItemSlot& RequiredItem : ItemsToFind)
	{
		const int32 AmountFound = HowManyOfItemsCanBeFoundInInventory(RequiredItem, InventorySlots);

		if (AmountFound < RequiredItem.Amount)
		{
			return false;
		}
	}

	return true;
}

int32 UInventoryComponent::HowManyOfItemsCanBeFoundInInventory(const FInventoryItemSlot& ItemToFind, const TArray<FInventoryItemSlot>& TargetArray) const
{
	bool bSuccess = false;
	const TArray<int32> FoundIndexes = FindExistingSlotIndexesOfSpecifiedInventoryItem(TargetArray, ItemToFind, bSuccess);

	// Non-stackable slots -> amount available is just how many slots matched.
	// TODO : 나중에 Stackable로 바뀌면 변경해야함

	return bSuccess ? FoundIndexes.Num() : 0;

	/*Stackable로 할경우 함수 기능*/
	/*
	bool bSuccess = false;
	const TArray<int32> FoundIndexes = FindExistingSlotIndexesOfSpecifiedInventoryItem(TargetArray, ItemToFind, bSuccess);

	if (!bSuccess)
	{
		return 0;
	}

	int32 TotalAmount = 0;
	for (const int32 SlotIndex : FoundIndexes)
	{
		TotalAmount += TargetArray[SlotIndex].Amount;
	}

	return TotalAmount;
	*/

}

TArray<int32> UInventoryComponent::FindExistingSlotIndexesOfSpecifiedInventoryItem(const TArray<FInventoryItemSlot>& TargetArray, const FInventoryItemSlot& ItemToFind, bool& bOutSuccess) const
{
	TArray<int32> FoundIndexes;

	for (int32 Index = 0; Index < TargetArray.Num(); ++Index)
	{
		if (UInventoryStatics::CheckIfInventoryItemEqual(TargetArray[Index], ItemToFind))
		{
			FoundIndexes.Add(Index);
		}
	}

	bOutSuccess = FoundIndexes.Num() > 0;
	return FoundIndexes;
}

void UInventoryComponent::RemoveItemFromInventoryAutomatically(const FInventoryItemSlot& ItemToRemove, int32 AmountToRemove)
{
	if (AmountToRemove <= 0)
	{
		return;
	}

	bool bSuccess = false;
	const TArray<int32> FoundIndexes = FindExistingSlotIndexesOfSpecifiedInventoryItem(InventorySlots, ItemToRemove, bSuccess);

	if (!bSuccess)
	{
		return;
	}

	const int32 NumToRemove = FMath::Min(AmountToRemove, FoundIndexes.Num());
	const int32 LastIndex = FoundIndexes.Num() - 1;

	for (int32 i = 0; i < NumToRemove; ++i)
	{
		const int32 SlotIndex = FoundIndexes[LastIndex - i];
		SetInventorySlotToEmptyByIndex(InventorySlots, SlotIndex);
	}
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
