// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Equipment/EquipmentComponent.h"
#include "Component/Inventory/ExtenedInventoryComponent.h"
#include "Utils/EquipmentStatics.h"
#include "Utils/SurvivalStatics.h"
#include "Types/EquipmentTypes.h"

void UEquipmentComponent::Equip(const FInventoryItemSlot& ItemToEquip,int32 Index)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	// 이 아이템이 장착 가능한지 확인 (FItem.CoupledDataTable을 통해 DT_Equipment 조회). 못 찾으면 아무 것도 하지 않는다.
	FEquipmentItem EquipmentInfo;
	if (!UEquipmentStatics::GetEquipmentInfoFromInventorySlot(ItemToEquip, EquipmentInfo))
	{
		return;
	}
	UExtenedInventoryComponent* InventoryComp = USurvivalStatics::GetComponentFromComponent<UExtenedInventoryComponent>(this);
	if (!InventoryComp)
	{
		return;
	}
	InventoryComp->RemoveItemAtSlotIndex(Index);
	SetEquipmentSlot(ItemToEquip);
	// 서버는 자기 자신의 OnRep_EquipmentItem을 받지 못하므로 직접 브로드캐스트
	OnEquipmentSlotUpdated.Broadcast(EquipmentItem);
}

void UEquipmentComponent::Unequip()
{
}

void UEquipmentComponent::TryExecutePrimaryEquipmentAction()
{
}

void UEquipmentComponent::SetEquipmentSlot(const FInventoryItemSlot& ItemToEquip)
{
	EquipmentItem = ItemToEquip;
}
