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

void UExtenedEquipmentComponent::Server_Equip_Implementation(const FInventoryItemSlot& ItemToEquip, int32 Index)
{
	Equip(ItemToEquip,Index);
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

void UExtenedEquipmentComponent::Equip(const FInventoryItemSlot& ItemToEquip, int32 Index)
{
}

void UExtenedEquipmentComponent::Unequip()
{
}

void UExtenedEquipmentComponent::TryExecutePrimaryEquipmentAction()
{
}

void UExtenedEquipmentComponent::SetEquipmentSlot(const FInventoryItemSlot& ItemToEquip)
{
}

void UExtenedEquipmentComponent::OnRep_EquipmentItem()
{
	// 서버는 자기 자신의 OnRep을 받지 못하므로, 서버 측 브로드캐스트는
	// Equip/Unequip 에서 처리하기
	OnEquipmentSlotUpdated.Broadcast(EquipmentItem);
}


