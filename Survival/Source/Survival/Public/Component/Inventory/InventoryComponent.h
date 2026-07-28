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

	void InitInventory();
	int32 CreateEmptySlot(TArray<FInventoryItemSlot>& TargetInventory);
	
};
