// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Building/ExtenedBuildingComponent.h"
#include "BuildingComponent.generated.h"

class ABuildableGhost;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UBuildingComponent : public UExtenedBuildingComponent
{
	GENERATED_BODY()
public:

	virtual void StartBuildMode(const FInventoryItemSlot& ItemSlot, int32 InventorySourceIndex) override;
	virtual void StopBuildMode() override;

protected:
	UFUNCTION()
	void HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

	virtual void BeginPlay() override;

	void BuildTick();
	void TraceBuildLocation();
	void SpawnGhostMesh();

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TSubclassOf<ABuildableGhost> GhostClass;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	float BuildTickInterval = 0.03f;

	UPROPERTY(EditDefaultsOnly, Category = "Building|Trace")
	TEnumAsByte<ETraceTypeQuery> BuildTraceChannel = TraceTypeQuery1;

	UPROPERTY(EditDefaultsOnly, Category = "Building|Trace")
	float BuildTraceStartOffset = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	float BuildTraceLength = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Building|Input")
	TObjectPtr<UInputMappingContext> BuildingInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Building|Input")
	TObjectPtr<UInputMappingContext> EquipmentInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Building|Input")
	int32 BuildingMappingPriority = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Building|Input")
	TObjectPtr<UInputAction> StopBuildModeAction;

	FTimerHandle BuildTimerHandle;
	bool bBuildModeOn = false;
	FDataTableRowHandle SelectedBuildableDataRow;
	FTransform CurrentBuildLocationTransform;

	UPROPERTY()
	TObjectPtr<ABuildableGhost> GhostMeshActor;
private:


};
