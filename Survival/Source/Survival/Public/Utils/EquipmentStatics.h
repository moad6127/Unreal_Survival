// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/InventoryTypes.h"
#include "Types/EquipmentTypes.h"
#include "EquipmentStatics.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UEquipmentStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// 장착 불가능한 아이템(CoupledDataTable 미할당)이면 false.
	UFUNCTION(BlueprintPure, Category = "Equipment")
	static bool GetEquipmentInfoFromInventorySlot(const FInventoryItemSlot& InventorySlot, FEquipmentItem& OutEquipmentItem);


};
