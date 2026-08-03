// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractionActor/BaseInteractActor.h"
#include "InteractLocation.generated.h"

/**
 * 
 */
class UInventoryComponent;

UCLASS()
class SURVIVAL_API AInteractLocation : public ABaseInteractActor
{
	GENERATED_BODY()
public:
	AInteractLocation();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;
};
