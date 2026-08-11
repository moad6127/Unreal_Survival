// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Equipment/ExtenedEquipmentComponent.h"
#include "Net/UnrealNetwork.h"
#include "Actors/EquipActor/EquipActor.h"

UExtenedEquipmentComponent::UExtenedEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

}

void UExtenedEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UExtenedEquipmentComponent, EquippedWeaponActor);
	DOREPLIFETIME(UExtenedEquipmentComponent, EquipmentItem);
}

void UExtenedEquipmentComponent::Server_Equip_Implementation(const FInventoryItemSlot& ItemToEquip)
{
	Equip(ItemToEquip);
}

void UExtenedEquipmentComponent::Server_Unequip_Implementation()
{
	Unequip();
}


void UExtenedEquipmentComponent::Server_TryExecutePrimaryEquipmentAction_Implementation()
{
	TryExecutePrimaryEquipmentAction();
}

// Called when the game starts
void UExtenedEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UExtenedEquipmentComponent::Equip(const FInventoryItemSlot& ItemToEquip)
{
}

void UExtenedEquipmentComponent::Unequip()
{
}

void UExtenedEquipmentComponent::TryExecutePrimaryEquipmentAction()
{
}


