// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractionActor/InteractLocation.h"
#include "Component/Inventory/InventoryComponent.h"
#include "Utils/SurvivalStatics.h"

AInteractLocation::AInteractLocation()
{
	bReplicates = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AInteractLocation::Server_ClearOwner_Implementation()
{
	bIsInUse = false;
	SetOwner(nullptr);
}

void AInteractLocation::Interact_Implementation(AController* InstigatorController)
{
	if (!IsValid(InstigatorController) || bIsInUse)
	{
		return;
	}

	APawn* InstigatorPawn = InstigatorController->GetPawn();
	if (!InstigatorPawn)
	{
		return;
	}
	UExtenedInventoryComponent* PlayerInventoryComponent = USurvivalStatics::GetComponentFromController<UExtenedInventoryComponent>(InstigatorController);
	if (!PlayerInventoryComponent)
	{
		return;
	}

	SetOwner(InstigatorController);
	if (bIsInUseTogether)
	{
		bIsInUse = true;
	}
	Client_ShowInventoryUI(InstigatorController, PlayerInventoryComponent);
}

void AInteractLocation::Client_ShowInventoryUI_Implementation(AController* OwningController, UExtenedInventoryComponent* PlayerInventoryComponent)
{
	if (APlayerController* PC = Cast<APlayerController>(OwningController))
	{
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;

		OnShowDualInventory(PC, PlayerInventoryComponent, InventoryComponent);
	}
	

}
