// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/EquipmentStatics.h"
#include "Utils/InventoryStatics.h"
#include "Engine/DataTable.h"

bool UEquipmentStatics::GetEquipmentInfoFromInventorySlot(const FInventoryItemSlot& InventorySlot, FEquipmentItem& OutEquipmentItem)
{
	FItem ItemInfo;
	if (!UInventoryStatics::GetInventoryItemInfoFromSlot(InventorySlot, ItemInfo))
	{
		return false;
	}

	if (!ItemInfo.CoupledDataTable.DataTable)
	{
		return false;
	}

	const FEquipmentItem* FoundRow = ItemInfo.CoupledDataTable.DataTable->FindRow<FEquipmentItem>(ItemInfo.CoupledDataTable.RowName, TEXT("GetEquipmentInfoFromInventorySlot"));
	if (!FoundRow)
	{
		return false;
	}

	OutEquipmentItem = *FoundRow;
	return true;
}
