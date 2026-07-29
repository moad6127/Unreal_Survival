// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/InventoryTypes.h"
#include "InventoryStatics.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UInventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Inventory")
	static bool GetInventoryItemInfoFromSlot(const FInventoryItemSlot& InSlot, FItem& OutItemInfo);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	static void GetGridRowAndColumn(int32 Index, int32 SlotsPerRow, int32& OutRow, int32& OutColumn);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	static bool CheckIfInventoryItemEqual(const FInventoryItemSlot& ItemSlotOne, const FInventoryItemSlot& ItemSlotTwo);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	static bool IsItemEmpty(const FInventoryItemSlot& InSlot, const FDataTableRowHandle& EmptyItem);
};
