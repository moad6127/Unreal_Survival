// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Crafting/CraftingComponent.h"
#include "Engine/DataTable.h"
#include "Component/Inventory/InventoryComponent.h"
#include "Utils/SurvivalStatics.h"

void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoPopulateRecipesFromDataTable)
	{
		SetDefaultRecipesFromDataTable();
	}
}

void UCraftingComponent::TryCraftItem(const FInventoryItemSlot& ItemToCraft)
{
	//이미 크래프팅중이라면 넘기기,
	if (bIsCrafting)
	{
		return;
	}

	if (!ItemToCraft.Item.DataTable)
	{
		return;
	}

	const FItem* ItemRow = ItemToCraft.Item.DataTable->FindRow<FItem>(ItemToCraft.Item.RowName, TEXT("ServerTryCraftItem"));
	if (!ItemRow || !ItemRow->Crafting.bIsCraftable)
	{
		return;
	}

	UExtenedInventoryComponent* InventoryComponent = USurvivalStatics::GetComponentFromActor<UExtenedInventoryComponent>(GetOwner());
	if (!InventoryComponent)
	{
		return;
	}

	if (!InventoryComponent->CanArrayOfItemsBeFoundInInventory(ItemRow->Crafting.Recipe))
	{
		UE_LOG(LogTemp, Log, TEXT("Not sufficient items to craft %s"), *ItemToCraft.Item.RowName.ToString());
		return;
	}

	for (const FInventoryItemSlot& RecipeIngredient : ItemRow->Crafting.Recipe)
	{
		InventoryComponent->Server_RemoveItemFromInventoryAutomatically(RecipeIngredient);
	}

	StartCrafting(ItemToCraft);
}

void UCraftingComponent::StartCrafting(const FInventoryItemSlot& ItemToStartCrafting)
{
	bIsCrafting = true;
	CurrentlyCraftingItem = ItemToStartCrafting;

	StartingCraftingTime = DefaultCraftingTime;
	CurrentCraftingTime = StartingCraftingTime;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (CraftingTimerHandle.IsValid())
	{
		TimerManager.UnPauseTimer(CraftingTimerHandle);
	}
	else
	{
		TimerManager.SetTimer(CraftingTimerHandle, this, &UCraftingComponent::TickCraftingTimer, CraftingTickInterval, true);
	}
}

void UCraftingComponent::TickCraftingTimer()
{
	CurrentCraftingTime -= CraftingTickInterval;

	if (CurrentCraftingTime > 0.f)
	{
		return;
	}

	GetWorld()->GetTimerManager().PauseTimer(CraftingTimerHandle);

	if (UExtenedInventoryComponent* InventoryComponent = USurvivalStatics::GetComponentFromActor<UExtenedInventoryComponent>(GetOwner()))
	{
		InventoryComponent->Server_TryAddItemToInventoryAutomatically(CurrentlyCraftingItem);
	}

	CurrentlyCraftingItem = FInventoryItemSlot();
	bIsCrafting = false;
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

