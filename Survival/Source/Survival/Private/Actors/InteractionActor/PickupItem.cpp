// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractionActor/PickupItem.h"
#include "Utils/InventoryStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Component/Inventory/InventoryComponent.h"
#include "Net/UnrealNetwork.h"

APickupItem::APickupItem()
{
	bReplicates = true;
	bIsInteractable = true;
}

void APickupItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateFromItemData();
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->SetSimulatePhysics(bSimulatePhysics);
}

void APickupItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APickupItem, InventoryItemSlot);
}

void APickupItem::Interact_Implementation(AController* InstigatorController)
{
	if (!InstigatorController)
	{
		return;
	}

	APawn* InstigatorPawn = InstigatorController->GetPawn();
	if (!InstigatorPawn)
	{
		return;
	}
	if (UInventoryComponent* InventoryComp = InstigatorPawn->FindComponentByClass<UInventoryComponent>())
	{
		InventoryComp->Server_TryAddItemToInventoryAutomatically(InventoryItemSlot);
	}
	Destroy();
}

void APickupItem::OnRep_InventoryItemSlot()
{
	UpdateFromItemData();
}

void APickupItem::UpdateFromItemData()
{
	FItem ItemData;
	if (!UInventoryStatics::GetInventoryItemInfoFromSlot(InventoryItemSlot, ItemData))
	{
		return;
	}
	ItemMesh->SetStaticMesh(ItemData.Generic.ItemMesh);
	InteractText = FText::Format(NSLOCTEXT("Pickup", "PickupPrompt", "[E] Pick up {0}"), ItemData.Generic.ItemName);
}
