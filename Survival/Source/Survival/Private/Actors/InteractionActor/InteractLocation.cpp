// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractionActor/InteractLocation.h"
#include "Component/Inventory/InventoryComponent.h"

AInteractLocation::AInteractLocation()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

