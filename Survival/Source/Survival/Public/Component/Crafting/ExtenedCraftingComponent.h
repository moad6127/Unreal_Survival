// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryTypes.h"
#include "ExtenedCraftingComponent.generated.h"



UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedCraftingComponent();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Crafting")
	void Server_TryCraftItem(const FInventoryItemSlot& ItemToCraft);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Crafting")
	void Server_StartCrafting(const FInventoryItemSlot& ItemToStartCrafting);
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void TryCraftItem(const FInventoryItemSlot& ItemToCraft);
	virtual void StartCrafting(const FInventoryItemSlot& ItemToStartCrafting);

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Crafting")
	bool bIsCrafting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crafting")
	TArray<FInventoryItemSlot> Recipes;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Crafting")
	FInventoryItemSlot CurrentlyCraftingItem;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Crafting")
	float StartingCraftingTime = 0.f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Crafting")
	float CurrentCraftingTime = 0.f;
};
