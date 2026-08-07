// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Crafting/CraftingComponent.h"
#include "Engine/DataTable.h"

void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoPopulateRecipesFromDataTable)
	{
		SetDefaultRecipesFromDataTable();
	}
}

void UCraftingComponent::SetDefaultRecipesFromDataTable()
{
	if (!ItemDataTable)
	{
		return;
	}
	for (const FName& RowName : ItemDataTable->GetRowNames())
	{
		const FItem* Row = ItemDataTable->FindRow<FItem>(RowName, TEXT("SetDefaultRecipesFromDataTable"));
		if (!Row || !Row->Crafting.bIsCraftable)
		{
			continue;
		}

		const bool bAlreadyKnown = Recipes.ContainsByPredicate([&RowName, this](const FInventoryItemSlot& Existing)
			{
				return Existing.Item.DataTable == ItemDataTable && Existing.Item.RowName == RowName;
			});

		if (bAlreadyKnown)
		{
			continue;
		}

		FInventoryItemSlot NewRecipeSlot;
		NewRecipeSlot.Item.DataTable = ItemDataTable;
		NewRecipeSlot.Item.RowName = RowName;
		NewRecipeSlot.Amount = 1;

		Recipes.Add(NewRecipeSlot);
	}
}

