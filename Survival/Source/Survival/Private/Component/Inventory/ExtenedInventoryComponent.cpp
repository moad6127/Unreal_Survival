// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/Inventory/ExtenedInventoryComponent.h"

UExtenedInventoryComponent::UExtenedInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UExtenedInventoryComponent::Server_TryAddItemToInventoryAutomatically_Implementation(const FInventoryItemSlot& ItemToAdd)
{
	TryAddItemToInventoryAutomatically(InventorySlots, ItemToAdd);
}

void UExtenedInventoryComponent::Server_DropItemBySlotIndex_Implementation(int32 Index)
{
	DropItemBySlotIndex(InventorySlots, Index);
}

void UExtenedInventoryComponent::Server_SpawnItem_Implementation(const FInventoryItemSlot& ItemToSpawn)
{
	SpawnItem(ItemToSpawn);
}


void UExtenedInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UExtenedInventoryComponent::FindEmptySlot(const TArray<FInventoryItemSlot>& TargetInventory, int32& OutIndex)
{
	return false;
}

void UExtenedInventoryComponent::AddItemToSlotByIndex(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd, int32 Index)
{
}

void UExtenedInventoryComponent::DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index)
{
}

void UExtenedInventoryComponent::TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd)
{
}

void UExtenedInventoryComponent::SpawnItem(const FInventoryItemSlot& ItemToSpawn)
{
}

