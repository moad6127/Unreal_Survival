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
