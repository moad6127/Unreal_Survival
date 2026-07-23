// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types/AttributeType.h"
#include "InventoryTypes.generated.h"


UENUM(BlueprintType)
enum class EInventoryAction : uint8
{
	None,
	Consume,
	Equip,
	Place
};

USTRUCT(BlueprintType)
struct FItemAttributeGeneric
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInventoryAction AllowedInventoryAction = EInventoryAction::None;
};

USTRUCT(BlueprintType)
struct FInventoryItemSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount = 0;
};

USTRUCT(BlueprintType)
struct FItemAttributeCrafting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsCraftable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsCraftable"))
	TArray<FInventoryItemSlot> Recipe;
};

USTRUCT(BlueprintType)
struct FItemAssignedAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAttributeTypes AttributeType = EAttributeTypes::None; // ← 아래 확인 필요

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Amount = 0.f;
};

USTRUCT(BlueprintType)
struct FItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemAttributeGeneric Generic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemAttributeCrafting Crafting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemAssignedAttribute AssignedAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle CoupledDataTable;
};
