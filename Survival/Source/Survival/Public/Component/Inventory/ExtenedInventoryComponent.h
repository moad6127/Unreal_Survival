// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "ExtenedInventoryComponent.generated.h"


class APickupItem;

UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedInventoryComponent();

	UFUNCTION(BlueprintCallable ,Server, Reliable)
	void Server_TryAddItemToInventoryAutomatically(const FInventoryItemSlot& ItemToAdd);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_DropItemBySlotIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SpawnItem(const FInventoryItemSlot& ItemToSpawn);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_MoveItemToSlotIndex(UExtenedInventoryComponent* SourceInventoryComponent, int32 SourceIndex, UExtenedInventoryComponent* DestinationInventoryComponent, int32 DestinationIndex);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsPlayerInventory() const { return bIsPlayerInventory; }
protected:
	virtual void BeginPlay() override;

	virtual bool FindEmptySlot(const TArray<FInventoryItemSlot>& TargetInventory, int32& OutIndex);
	virtual void AddItemToSlotByIndex(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd, int32 Index);
	virtual void DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index);
	virtual void TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd);
	virtual void SpawnItem(const FInventoryItemSlot & ItemToSpawn);
	virtual void SetInventorySlotToEmptyByIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index);

	
	virtual void MoveItemToSlotIndex(UExtenedInventoryComponent* SourceInventoryComponent, int32 SourceIndex, UExtenedInventoryComponent* DestinationInventoryComponent, int32 DestinationIndex);




	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Inventory")
	TArray<FInventoryItemSlot> InventorySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 DefaultInventorySlotAmount = 24;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	FDataTableRowHandle EmptySlotItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 SlotsPerRow = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<APickupItem> PickupItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	bool bIsPlayerInventory = false;
	
};
