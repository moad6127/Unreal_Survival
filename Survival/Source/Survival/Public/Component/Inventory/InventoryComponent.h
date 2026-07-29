// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Inventory/ExtenedInventoryComponent.h"
#include "InventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UInventoryComponent : public UExtenedInventoryComponent
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;

	virtual bool FindEmptySlot(const TArray<FInventoryItemSlot>& TargetInventory, int32& OutIndex) override;
	virtual void AddItemToSlotByIndex(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd, int32 Index) override;
	virtual void DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index) override;
	virtual void TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd) override;
	virtual void SpawnItem(const FInventoryItemSlot& ItemToSpawn) override;

	void InitInventory();
	int32 CreateEmptySlot(TArray<FInventoryItemSlot>& TargetInventory);
	
};
