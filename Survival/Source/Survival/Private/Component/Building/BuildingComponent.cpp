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



	const FItem* Item = ItemSlot.Item.GetRow<FItem>(TEXT("UBuildingComponent::StartBuildMode"));
	if (!Item)
	{
		return;
	}

	const FBuildableData* BuildableData = Item->CoupledDataTable.GetRow<FBuildableData>(TEXT("UBuildingComponent_Basic::StartBuildMode"));
	if (!BuildableData)
	{
		// 버더블 구조체를 못 찾으면 빌드 모드를 시작하지 않음
		return;
	}

	PendingBuildItemSlot = ItemSlot;
	PendingInventorySourceIndex = InventorySourceIndex;

	SelectedBuildableDataRow = Item->CoupledDataTable;
	SelectedBuildableStructure = *BuildableData;
	bSelectedBuildableStructureValid = true;
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
	SelectedBuildableStructure = FBuildableData();
	bSelectedBuildableStructureValid = false;

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
	const bool bHit = USurvivalStatics::TraceFromActiveCamera(PC, BuildTraceChannel, ActorsToIgnore, BuildTraceStartOffset, BuildTraceLength, HitResult);
	
	if(bHit)
	{
		OnHitLogic(HitResult);
		return;
	}

	LastHitActor = nullptr;
	LastHitComponent = nullptr;
	CurrentBuildLocationTransform.SetLocation(HitResult.TraceEnd);

	if (GhostMeshActor)
	{
		GhostMeshActor->SetCanBuild(false);
		SetGhostMeshLocation();
	}
}

void UBuildingComponent::OnHitLogic(const FHitResult& HitResult)
{
	LastHitActor = HitResult.GetActor();
	LastHitComponent = HitResult.GetComponent();

	CurrentBuildLocationTransform.SetLocation(HitResult.Location);

	FTransform SnapTransform;
	const bool bSnapFound = DetectSnappingPoint(LastHitActor, LastHitComponent, SnapTransform);
	if (bSnapFound)
	{
		CurrentBuildLocationTransform = SnapTransform;
	}

	const bool bOverlapping = CheckForOverlap();
	bool bCanBuild = !bOverlapping;

	// 스냅 포인트에만 배치 가능한 것들 인데 스냅 포인트를 못 찾았으면 무조건 불가
	if (bSelectedBuildableStructureValid && SelectedBuildableStructure.bCanOnlyBePlacedAtSnappingPoints && !bSnapFound)
	{
		bCanBuild = false;
	}

	if (GhostMeshActor)
	{
		GhostMeshActor->SetCanBuild(bCanBuild);
		SetGhostMeshLocation();
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

void UBuildingComponent::SetGhostMeshLocation()
{
	if (GhostMeshActor)
	{
		GhostMeshActor->SetActorTransform(CurrentBuildLocationTransform);
	}
}

bool UBuildingComponent::DetectSnappingPoint(AActor* HitActor, UPrimitiveComponent* HitComponent, FTransform& OutTransform) const
{
	return false;
}

bool UBuildingComponent::CheckForOverlap() const
{
	return false;
}
