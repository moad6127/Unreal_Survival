// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "ExtenedBuildingComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedBuildingComponent();

	UFUNCTION(BlueprintCallable, Category = "Building")
	virtual void StartBuildMode(const FInventoryItemSlot& ItemSlot, int32 InventorySourceIndex);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Building")
	virtual void StopBuildMode();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Building")
	void Server_SpawnBuildable(const FTransform& SpawnTransform, const FDataTableRowHandle& BuildableDataRow, bool bCanBuild, int32 InventorySourceIndex);

protected:
	virtual void BeginPlay() override;

	virtual void SpawnBuildable(const FTransform& SpawnTransform, const FDataTableRowHandle& BuildableDataRow, bool bCanBuild, int32 InventorySourceIndex);

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	FInventoryItemSlot PendingBuildItemSlot;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	int32 PendingInventorySourceIndex = INDEX_NONE;
};
