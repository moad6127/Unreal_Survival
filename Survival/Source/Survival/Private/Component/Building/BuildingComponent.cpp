// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Building/BuildingComponent.h"

void UBuildingComponent::StartBuildMode(const FInventoryItemSlot& ItemSlot, int32 InventorySourceIndex)
{
	PendingBuildItemSlot = ItemSlot;
	PendingInventorySourceIndex = InventorySourceIndex;

	if (const FItem* Item = ItemSlot.Item.GetRow<FItem>(TEXT("UBuildingComponent::StartBuildMode")))
	{
		UE_LOG(LogTemp, Log, TEXT("Try to build %s"), *Item->Generic.ItemName.ToString());
	}
}

void UBuildingComponent::StopBuildMode()
{
	PendingBuildItemSlot = FInventoryItemSlot();
	PendingInventorySourceIndex = INDEX_NONE;
}
