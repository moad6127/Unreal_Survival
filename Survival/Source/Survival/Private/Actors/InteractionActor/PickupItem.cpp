// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractionActor/PickupItem.h"
#include "Utils/InventoryStatics.h"
#include "Components/StaticMeshComponent.h"

APickupItem::APickupItem()
{
	bReplicates = true;
	bIsInteractable = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetRootComponent());
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void APickupItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateFromItemData();
}

void APickupItem::Interact_Implementation(AController* InstigatorController)
{
	Super::Interact_Implementation(InstigatorController);

	//TODO : 인터렉트 하기(인벤토리에 넣는것등등...)
	FItem ItemData;
	if (UInventoryStatics::GetInventoryItemInfoFromSlot(InventoryItemSlot, ItemData))
	{
		UE_LOG(LogTemp, Log, TEXT("%s is trying to pick up %s"),
			*GetNameSafe(InstigatorController), *ItemData.Generic.ItemName.ToString());
	}
}

void APickupItem::UpdateFromItemData()
{
	FItem ItemData;
	if (!UInventoryStatics::GetInventoryItemInfoFromSlot(InventoryItemSlot, ItemData))
	{
		return;
	}
	ItemMesh->SetStaticMesh(ItemData.Generic.ItemMesh);
	InteractText = FText::Format(NSLOCTEXT("Pickup", "PickupPrompt", "Pick up {0}"), ItemData.Generic.ItemName);
}
