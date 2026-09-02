// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Building/BuildingComponent.h"
#include "Utils/SurvivalStatics.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Types/InventoryTypes.h"
#include "Actors/BuildableActors/BuildableGhost.h"

void UBuildingComponent::StartBuildMode(const FInventoryItemSlot& ItemSlot, int32 InventorySourceIndex)
{
	if (bBuildModeOn)
	{
		StopBuildMode();
	}


	PendingBuildItemSlot = ItemSlot;
	PendingInventorySourceIndex = InventorySourceIndex;

	const FItem* Item = ItemSlot.Item.GetRow<FItem>(TEXT("UBuildingComponent::StartBuildMode"));
	if (!Item)
	{
		return;
	}
	SelectedBuildableDataRow = Item->CoupledDataTable;
	bBuildModeOn = true;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().UnPauseTimer(BuildTimerHandle);
	}
	if (APlayerController* PC = USurvivalStatics::GetPlayerControllerFromComponent(this))
	{
		USurvivalStatics::LinkInputMappingContext(PC, BuildingInputMappingContext, BuildingMappingPriority);
		USurvivalStatics::UnlinkInputMappingContext(PC, EquipmentInputMappingContext);
	}

	SpawnGhostMesh();
}

void UBuildingComponent::StopBuildMode()
{
	if (!bBuildModeOn)
	{
		return;
	}
	PendingBuildItemSlot = FInventoryItemSlot();
	PendingInventorySourceIndex = INDEX_NONE;

	bBuildModeOn = false;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().PauseTimer(BuildTimerHandle);
	}

	if (GhostMeshActor)
	{
		GhostMeshActor->Destroy();
		GhostMeshActor = nullptr;
	}

	if (APlayerController* PC = USurvivalStatics::GetPlayerControllerFromComponent(this))
	{
		USurvivalStatics::UnlinkInputMappingContext(PC, BuildingInputMappingContext);
		USurvivalStatics::LinkInputMappingContext(PC, EquipmentInputMappingContext, 0);
	}
}

void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(BuildTimerHandle, this, &UBuildingComponent::BuildTick, BuildTickInterval, true);
		World->GetTimerManager().PauseTimer(BuildTimerHandle);
	}

	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		OwnerPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UBuildingComponent::HandleControllerChanged);
		if (AController* CurrentController = OwnerPawn->GetController())
		{
			HandleControllerChanged(OwnerPawn, nullptr, CurrentController);
		}
	}
}
void UBuildingComponent::HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	APlayerController* PC = Cast<APlayerController>(NewController);
	if (!IsValid(PC))
	{
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}

	if (StopBuildModeAction)
	{
		EnhancedInputComponent->BindAction(StopBuildModeAction, ETriggerEvent::Started, this, &UBuildingComponent::StopBuildMode);
	}
}

void UBuildingComponent::BuildTick()
{
	if (bBuildModeOn)
	{
		TraceBuildLocation();
	}
}

void UBuildingComponent::TraceBuildLocation()
{
	APlayerController* PC = USurvivalStatics::GetPlayerControllerFromComponent(this);
	if (!PC)
	{
		return;
	}

	TArray<AActor*> ActorsToIgnore;
	if (AActor* OwnerActor = GetOwner())
	{
		ActorsToIgnore.Add(OwnerActor);
	}

	FHitResult HitResult;
	if (USurvivalStatics::TraceFromActiveCamera(PC, BuildTraceChannel, ActorsToIgnore, BuildTraceStartOffset, BuildTraceLength, HitResult))
	{
		CurrentBuildLocationTransform.SetLocation(HitResult.Location);

		if (GhostMeshActor)
		{
			GhostMeshActor->SetActorLocation(HitResult.Location);
		}
	}
}

void UBuildingComponent::SpawnGhostMesh()
{
	UWorld* World = GetWorld();
	if (!World || !GhostClass)
	{
		return;
	}

	ABuildableGhost* NewGhost = World->SpawnActorDeferred<ABuildableGhost>(GhostClass, CurrentBuildLocationTransform);
	if (!NewGhost)
	{
		return;
	}

	NewGhost->BuildableDataRow = SelectedBuildableDataRow;
	NewGhost->FinishSpawning(CurrentBuildLocationTransform);

	GhostMeshActor = NewGhost;
}
