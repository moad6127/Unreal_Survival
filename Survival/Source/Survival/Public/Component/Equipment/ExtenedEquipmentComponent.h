// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "Types/EquipmentTypes.h"
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

	// 드래그 앤 드롭 등, 지정해서 언이큅하고 싶을 때 사용
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Equipment")
	void Server_UnequipToSlot(int32 DestinationIndex);


	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Equipment")
	void Server_TryExecutePrimaryEquipmentAction();

	UFUNCTION(BlueprintPure, Category = "Equipment")
	FInventoryItemSlot GetEquipmentSlot() const { return EquipmentItem; }

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotUpdated OnEquipmentSlotUpdated;

protected:
	virtual void BeginPlay() override;

	virtual void Equip(const FInventoryItemSlot& ItemToEquip, int32 Index);
	virtual void Unequip();
	virtual void UnequipToSlot(int32 DestinationIndex);
	virtual void TryExecutePrimaryEquipmentAction();
	virtual void SetEquipmentSlot(const FInventoryItemSlot& ItemToEquip);


	virtual void SpawnAndAttach(const FEquipmentItem& EquipmentInfoToSpawn);
	virtual void DetachEquipment();
	virtual USkeletalMeshComponent* GetOwnerMesh() const;

	UFUNCTION()
	void OnRep_EquipmentItem();

	// 월드에 스폰되어 손에 붙는 장착 무기 액터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<AEquipActor> EquippedWeaponActor;

	/*현재 장착된 아이템
	* 장착아이템을 여러개 할경우 배열로 다시 생성하기
	*/
	UPROPERTY(ReplicatedUsing = OnRep_EquipmentItem, EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FInventoryItemSlot EquipmentItem;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<AEquipActor> EquipActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FDataTableRowHandle EmptyItem;
};
