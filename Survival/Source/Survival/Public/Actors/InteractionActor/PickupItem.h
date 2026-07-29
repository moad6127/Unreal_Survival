// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractionActor/BaseInteractActor.h"
#include "Types/InventoryTypes.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API APickupItem : public ABaseInteractActor
{
	GENERATED_BODY()
public:

	APickupItem();
	void SetInventoryItemSlot(const FInventoryItemSlot& InSlot) { InventoryItemSlot = InSlot; }
	void SetSimulatePhysics(bool bInSimulate) { bSimulatePhysics = bInSimulate; }

	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(AController* InstigatorController) override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	FInventoryItemSlot InventoryItemSlot;

private:
	void UpdateFromItemData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	bool bSimulatePhysics = false;
};
