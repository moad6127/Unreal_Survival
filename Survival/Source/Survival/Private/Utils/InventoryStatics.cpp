// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/InventoryStatics.h"

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
