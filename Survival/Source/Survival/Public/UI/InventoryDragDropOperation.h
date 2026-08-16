// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Types/InventoryTypes.h"
#include "InventoryDragDropOperation.generated.h"

/**
 * 
 */
class UExtenedInventoryComponent;
class UExtenedEquipmentComponent;

UCLASS()
class SURVIVAL_API UInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UExtenedInventoryComponent> SourceInventoryComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UExtenedEquipmentComponent> SourceEquipmentComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 SourceSlotIndex = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bEquipped = false;

	// 드래그 중 위젯 아이콘 표시용 (UI 전용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FInventoryItemSlot SourceItemSlot;


};
