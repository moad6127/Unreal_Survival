// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/Inventory/ExtenedInventoryComponent.h"
#include "Utils/InventoryStatics.h"
#include "Net/UnrealNetwork.h"

UExtenedInventoryComponent::UExtenedInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UExtenedInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UExtenedInventoryComponent, InventorySlots);
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

void UExtenedInventoryComponent::Server_ConsumeItemBySlotIndex_Implementation(UExtenedInventoryComponent* SourceInventoryComponent, int32 Index)
{
	if (!SourceInventoryComponent)
	{
		return;
	}
	SourceInventoryComponent->ConsumeItemBySlotIndex(SourceInventoryComponent->InventorySlots, Index);
}

void UExtenedInventoryComponent::Server_RemoveItemFromInventoryAutomatically_Implementation(const FInventoryItemSlot& ItemToRemove, int32 AmountToRemove)
{
	RemoveItemFromInventoryAutomatically(ItemToRemove,AmountToRemove);
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

void UExtenedInventoryComponent::ConsumeItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index)
{
}

void UExtenedInventoryComponent::RemoveItemFromInventoryAutomatically(const FInventoryItemSlot& ItemToRemove, int32 AmountToRemove)
{
}

bool UExtenedInventoryComponent::CanArrayOfItemsBeFoundInInventory(const TArray<FInventoryItemSlot>& ItemsToFind) const
{
	return false;
}
int32 UExtenedInventoryComponent::HowManyOfItemsCanBeFoundInInventory(const FInventoryItemSlot& ItemToFind, const TArray<FInventoryItemSlot>& TargetArray) const
{
	return int32();
}
TArray<int32> UExtenedInventoryComponent::FindExistingSlotIndexesOfSpecifiedInventoryItem(const TArray<FInventoryItemSlot>& TargetArray, const FInventoryItemSlot& ItemToFind, bool& bOutSuccess) const
{
	return TArray<int32>();
}

void UExtenedInventoryComponent::RemoveItemAtSlotIndex(int32 Index)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	SetInventorySlotToEmptyByIndex(InventorySlots, Index);
}

bool UExtenedInventoryComponent::AddItemAtSlotIndex(const FInventoryItemSlot& ItemToAdd, int32 Index)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	if (!InventorySlots.IsValidIndex(Index))
	{
		return false;
	}

	if (!UInventoryStatics::IsItemEmpty(InventorySlots[Index], EmptySlotItem))
	{
		return false;
	}

	AddItemToSlotByIndex(InventorySlots, ItemToAdd, Index);
	return true;
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
	OnInventorySlotUpdated.Broadcast(Index, EmptySlot);
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

void UExtenedInventoryComponent::OnRep_InventorySlots()
{
	for (int32 Index = 0; Index < InventorySlots.Num(); Index++)
	{
		const bool bHadPreviousValue = InventorySlotsPrevious.IsValidIndex(Index);
		const bool bShouldUpdate = !bHadPreviousValue || !UInventoryStatics::CheckIfInventoryItemEqual(InventorySlots[Index], InventorySlotsPrevious[Index]);
		if (bShouldUpdate)
		{
			OnInventorySlotUpdated.Broadcast(Index, InventorySlots[Index]);
		}
	}
	InventorySlotsPrevious = InventorySlots;
}

