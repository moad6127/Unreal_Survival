// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Crafting/ExtenedCraftingComponent.h"
#include "Net/UnrealNetwork.h"

UExtenedCraftingComponent::UExtenedCraftingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UExtenedCraftingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UExtenedCraftingComponent, bIsCrafting);
	DOREPLIFETIME(UExtenedCraftingComponent, CurrentlyCraftingItem);
	DOREPLIFETIME(UExtenedCraftingComponent, StartingCraftingTime);
	DOREPLIFETIME(UExtenedCraftingComponent, CurrentCraftingTime);
}

void UExtenedCraftingComponent::Server_TryCraftItem_Implementation(const FInventoryItemSlot& ItemToCraft)
{
	TryCraftItem(ItemToCraft);
}

void UExtenedCraftingComponent::Server_StartCrafting_Implementation(const FInventoryItemSlot& ItemToStartCrafting)
{
	StartCrafting(ItemToStartCrafting);
}

void UExtenedCraftingComponent::TryCraftItem(const FInventoryItemSlot& ItemToCraft)
{
}

void UExtenedCraftingComponent::StartCrafting(const FInventoryItemSlot& ItemToStartCrafting)
{
}

void UExtenedCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

