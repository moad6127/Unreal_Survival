// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/InventoryStatics.h"
#include "Component/Inventory/ExtenedInventoryComponent.h"

bool UInventoryStatics::GetInventoryItemInfoFromSlot(const FInventoryItemSlot& InSlot, FItem& OutItemInfo)
{
	if (!InSlot.Item.DataTable)
	{
		return false;
	}
	const FItem* FoundRow = InSlot.Item.DataTable->FindRow<FItem>(InSlot.Item.RowName, TEXT("GetInventoryItemInfoFromSlot"));
	if (!FoundRow)
	{
		return false;
	}

	OutItemInfo = *FoundRow;
	return true;
}

void UInventoryStatics::GetGridRowAndColumn(int32 Index, int32 SlotsPerRow, int32& OutRow, int32& OutColumn)
{
	OutRow = Index / SlotsPerRow;
	OutColumn = Index % SlotsPerRow;
}

bool UInventoryStatics::CheckIfInventoryItemEqual(const FInventoryItemSlot& ItemSlotOne, const FInventoryItemSlot& ItemSlotTwo)
{
	return ItemSlotOne.Item.RowName == ItemSlotTwo.Item.RowName;
}

bool UInventoryStatics::IsItemEmpty(const FInventoryItemSlot& InSlot, const FDataTableRowHandle& EmptyItem)
{
	return InSlot.Item.RowName == EmptyItem.RowName;
}

bool UInventoryStatics::WhichInventoryComponentIsFromPlayer(UExtenedInventoryComponent* ComponentOne, UExtenedInventoryComponent* ComponentTwo, UExtenedInventoryComponent*& OutPlayerInventoryComponent)
{
	if (ComponentOne && ComponentOne->IsPlayerInventory())
	{
		OutPlayerInventoryComponent = ComponentOne;
		return true;
	}

	if (ComponentTwo && ComponentTwo->IsPlayerInventory())
	{
		OutPlayerInventoryComponent = ComponentTwo;
		return true;
	}

	OutPlayerInventoryComponent = nullptr;
	return false;
}
