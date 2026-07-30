// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/Inventory/ExtenedInventoryComponent.h"
#include "Utils/InventoryStatics.h"

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

void UExtenedInventoryComponent::Server_MoveItemToSlotIndex_Implementation(UExtenedInventoryComponent* SourceInventoryComponent, int32 SourceIndex, UExtenedInventoryComponent* DestinationInventoryComponent, int32 DestinationIndex)
{
	MoveItemToSlotIndex(SourceInventoryComponent, SourceIndex, DestinationInventoryComponent, DestinationIndex);
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

void UExtenedInventoryComponent::SetInventorySlotToEmptyByIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index)
{
	if (!TargetInventory.IsValidIndex(Index))
	{
		return;
	}

	FInventoryItemSlot EmptySlot;
	EmptySlot.Item = EmptySlotItem;
	EmptySlot.Amount = 1;
	TargetInventory[Index] = EmptySlot;
}

void UExtenedInventoryComponent::MoveItemToSlotIndex(UExtenedInventoryComponent* SourceInventoryComponent, int32 SourceIndex, UExtenedInventoryComponent* DestinationInventoryComponent, int32 DestinationIndex)
{
	if (!SourceInventoryComponent || !DestinationInventoryComponent)
	{
		return;
	}

	if (SourceInventoryComponent == DestinationInventoryComponent && SourceIndex == DestinationIndex)
	{
		return;
	}

	if (!SourceInventoryComponent->InventorySlots.IsValidIndex(SourceIndex) ||
		!DestinationInventoryComponent->InventorySlots.IsValidIndex(DestinationIndex))
	{
		return;
	}

	const bool bDestinationEmpty = UInventoryStatics::IsItemEmpty(
		DestinationInventoryComponent->InventorySlots[DestinationIndex],
		DestinationInventoryComponent->EmptySlotItem);

	if (!bDestinationEmpty)
	{
		// 지금은 빈 슬롯에만 이동 허용. 스왑은 나중에 필요하면 추가.
		return;
	}
	const FInventoryItemSlot ItemToMove = SourceInventoryComponent->InventorySlots[SourceIndex];

	DestinationInventoryComponent->AddItemToSlotByIndex(DestinationInventoryComponent->InventorySlots, ItemToMove, DestinationIndex);
	SourceInventoryComponent->SetInventorySlotToEmptyByIndex(SourceInventoryComponent->InventorySlots, SourceIndex);
}

