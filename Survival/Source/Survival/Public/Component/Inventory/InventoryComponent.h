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
public:

protected:

	virtual void BeginPlay() override;

	virtual bool FindEmptySlot(const TArray<FInventoryItemSlot>& TargetInventory, int32& OutIndex) override;
	virtual void AddItemToSlotByIndex(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd, int32 Index) override;
	virtual void DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index) override;
	virtual void TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd) override;
	virtual void SpawnItem(const FInventoryItemSlot& ItemToSpawn) override;
	virtual void ConsumeItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index) override;
	virtual bool CanArrayOfItemsBeFoundInInventory(const TArray<FInventoryItemSlot>& ItemsToFind) const override;
	virtual int32 HowManyOfItemsCanBeFoundInInventory(const FInventoryItemSlot& ItemToFind, const TArray<FInventoryItemSlot>& TargetArray) const override;
	virtual TArray<int32> FindExistingSlotIndexesOfSpecifiedInventoryItem(const TArray<FInventoryItemSlot>& TargetArray, const FInventoryItemSlot& ItemToFind, bool& bOutSuccess) const override;
	virtual void RemoveItemFromInventoryAutomatically(const FInventoryItemSlot& ItemToRemove, int32 AmountToRemove) override;




	void InitInventory();
	int32 CreateEmptySlot(TArray<FInventoryItemSlot>& TargetInventory);
	
};
