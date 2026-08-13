// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "ExtenedEquipmentComponent.generated.h"

class AEquipActor;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentSlotUpdated, FInventoryItemSlot, EquippedItem);

UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedEquipmentComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Equipment")
	void Server_Equip(const FInventoryItemSlot& ItemToEquip, int32 Index);

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Equipment")
	void Server_Unequip();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Equipment")
	void Server_TryExecutePrimaryEquipmentAction();

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotUpdated OnEquipmentSlotUpdated;

protected:
	virtual void BeginPlay() override;

	virtual void Equip(const FInventoryItemSlot& ItemToEquip, int32 Index);
	virtual void Unequip();
	virtual void TryExecutePrimaryEquipmentAction();
	virtual void SetEquipmentSlot(const FInventoryItemSlot& ItemToEquip);

	UFUNCTION()
	void OnRep_EquipmentItem();

	// 월드에 스폰되어 손에 붙는 장착 무기 액터
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<AEquipActor> EquippedWeaponActor;

	/*현재 장착된 아이템
	* 장착아이템을 여러개 할경우 배열로 다시 생성하기
	*/
	UPROPERTY(ReplicatedUsing = OnRep_EquipmentItem, EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FInventoryItemSlot EquipmentItem;
};
