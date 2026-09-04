// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Building/ExtenedBuildingComponent.h"

UExtenedBuildingComponent::UExtenedBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

}

void UExtenedBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UExtenedBuildingComponent::StartBuildMode(const FInventoryItemSlot& ItemSlot, int32 InventorySourceIndex)
{

}

void UExtenedBuildingComponent::StopBuildMode_Implementation()
{
	PendingBuildItemSlot = FInventoryItemSlot();
	PendingInventorySourceIndex = INDEX_NONE;
}

void UExtenedBuildingComponent::Server_SpawnBuildable_Implementation(const FTransform& SpawnTransform, const FDataTableRowHandle& BuildableDataRow, bool bCanBuild, int32 InventorySourceIndex)
{
	SpawnBuildable(SpawnTransform, BuildableDataRow, bCanBuild, InventorySourceIndex);
}

void UExtenedBuildingComponent::SpawnBuildable(const FTransform& SpawnTransform, const FDataTableRowHandle& BuildableDataRow, bool bCanBuild, int32 InventorySourceIndex)
{

}





