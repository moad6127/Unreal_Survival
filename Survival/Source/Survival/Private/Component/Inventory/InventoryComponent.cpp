// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/InventoryComponent.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InitInventory();
}

void UInventoryComponent::InitInventory()
{
	for (int32 Index = 0; Index < DefaultInventorySlotAmount; Index++)
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
