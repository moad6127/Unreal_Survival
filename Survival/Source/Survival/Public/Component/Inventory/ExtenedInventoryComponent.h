// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "ExtenedInventoryComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedInventoryComponent();

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Inventory")
	TArray<FInventoryItemSlot> InventorySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 DefaultInventorySlotAmount = 24;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	FDataTableRowHandle EmptySlotItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 SlotsPerRow = 5;
	
};
