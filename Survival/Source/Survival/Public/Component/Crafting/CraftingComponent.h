// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Crafting/ExtenedCraftingComponent.h"
#include "CraftingComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UCraftingComponent : public UExtenedCraftingComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SetDefaultRecipesFromDataTable();

	UPROPERTY(EditDefaultsOnly, Category = "Crafting")
	TObjectPtr<UDataTable> ItemDataTable = nullptr;

	UPROPERTY(EditAnywhere, Category = "Crafting")
	bool bAutoPopulateRecipesFromDataTable = false;

protected:
	virtual void BeginPlay() override;
};
