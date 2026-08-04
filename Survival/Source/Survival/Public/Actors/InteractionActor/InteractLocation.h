// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractionActor/BaseInteractActor.h"
#include "InteractLocation.generated.h"

/**
 * 
 */
class UInventoryComponent;
class UExtenedInventoryComponent;

UCLASS()
class SURVIVAL_API AInteractLocation : public ABaseInteractActor
{
	GENERATED_BODY()
public:
	AInteractLocation();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void Server_ClearOwner();
protected:
	virtual void Interact_Implementation(AController* InstigatorController) override;

	UFUNCTION(Client, Reliable)
	void Client_ShowInventoryUI(AController* OwningController, UExtenedInventoryComponent* PlayerInventoryComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnShowDualInventory(APlayerController* OwningController, UExtenedInventoryComponent* SourceInventory, UExtenedInventoryComponent* TargetInventory);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	/*
	* 여러 플레이어가 동시에 사용가능한지 체크
	* Check whether multiple players can use it simultaneously
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	bool bIsInUseTogether = false;

	bool bIsInUse = false;
};
