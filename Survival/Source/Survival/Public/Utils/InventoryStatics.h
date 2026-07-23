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

};
