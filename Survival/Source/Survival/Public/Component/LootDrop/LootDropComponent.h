// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "LootDropComponent.generated.h"

class APickupItem;

USTRUCT(BlueprintType)
struct FLootDropEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Loot")
	FDataTableRowHandle Item;

	UPROPERTY(EditAnywhere, Category = "Loot", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DropChance = 1.f;

	UPROPERTY(EditAnywhere, Category = "Loot")
	int32 MinQuantity = 1;

	UPROPERTY(EditAnywhere, Category = "Loot")
	int32 MaxQuantity = 1;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API ULootDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULootDropComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnDeath();

	void SpawnLootItem(const FLootDropEntry& Entry);

	UPROPERTY(EditAnywhere, Category = "Loot")
	TSubclassOf<APickupItem> PickupItemClass;

	UPROPERTY(EditAnywhere, Category = "Loot")
	TArray<FLootDropEntry> LootTable;

private:
	bool bHasDroppedLoot = false;
};
