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
}

void UExtenedCraftingComponent::Server_TryCraftItem_Implementation(const FInventoryItemSlot& ItemToCraft)
{
}

void UExtenedCraftingComponent::Server_StartCrafting_Implementation()
{
}


void UExtenedCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

