// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "ExtenedInventoryComponent.generated.h"


class APickupItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotUpdated, int32, SlotIndex, FInventoryItemSlot, UpdatedSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemConsumed, FInventoryItemSlot, ConsumedItem);


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedInventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION(BlueprintCallable ,Server, Reliable)
	void Server_TryAddItemToInventoryAutomatically(const FInventoryItemSlot& ItemToAdd);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_DropItemBySlotIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SpawnItem(const FInventoryItemSlot& ItemToSpawn);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_MoveItemToSlotIndex(UExtenedInventoryComponent* SourceInventoryComponent, int32 SourceIndex, UExtenedInventoryComponent* DestinationInventoryComponent, int32 DestinationIndex);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ConsumeItemBySlotIndex(UExtenedInventoryComponent* SourceInventoryComponent, int32 Index);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Inventory")
	void Server_RemoveItemFromInventoryAutomatically(const FInventoryItemSlot& ItemToRemove, int32 AmountToRemove = 1);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsPlayerInventory() const { return bIsPlayerInventory; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
	virtual bool CanArrayOfItemsBeFoundInInventory(const TArray<FInventoryItemSlot>& ItemsToFind) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	virtual int32 HowManyOfItemsCanBeFoundInInventory(const FInventoryItemSlot& ItemToFind, const TArray<FInventoryItemSlot>& TargetArray) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	virtual TArray<int32> FindExistingSlotIndexesOfSpecifiedInventoryItem(const TArray<FInventoryItemSlot>& TargetArray, const FInventoryItemSlot& ItemToFind, bool& bOutSuccess) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemAtSlotIndex(int32 Index);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotUpdated OnInventorySlotUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemConsumed OnItemConsumed;
protected:
	virtual void BeginPlay() override;

	virtual bool FindEmptySlot(const TArray<FInventoryItemSlot>& TargetInventory, int32& OutIndex);
	virtual void AddItemToSlotByIndex(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd, int32 Index);
	virtual void DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index);
	virtual void TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd);
	virtual void SpawnItem(const FInventoryItemSlot & ItemToSpawn);
	virtual void SetInventorySlotToEmptyByIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index);
	virtual void ConsumeItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index);
	virtual void RemoveItemFromInventoryAutomatically(const FInventoryItemSlot& ItemToRemove, int32 AmountToRemove = 1);
	virtual void MoveItemToSlotIndex(UExtenedInventoryComponent* SourceInventoryComponent, int32 SourceIndex, UExtenedInventoryComponent* DestinationInventoryComponent, int32 DestinationIndex);


	UFUNCTION()
	void OnRep_InventorySlots();


	UPROPERTY(ReplicatedUsing = OnRep_InventorySlots, EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItemSlot> InventorySlots;

	TArray<FInventoryItemSlot> InventorySlotsPrevious;

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
