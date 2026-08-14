// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Equipment/ExtenedEquipmentComponent.h"
#include "EquipmentComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UEquipmentComponent : public UExtenedEquipmentComponent
{
	GENERATED_BODY()
	
protected:

	virtual void Equip(const FInventoryItemSlot& ItemToEquip, int32 Index) override;
	virtual void Unequip() override;
	virtual void TryExecutePrimaryEquipmentAction() override;
	virtual void SetEquipmentSlot(const FInventoryItemSlot& ItemToEquip) override;
	virtual void SpawnAndAttach(const FEquipmentItem& EquipmentInfoToSpawn) override;
	virtual void DetachEquipment() override;
private:

};
