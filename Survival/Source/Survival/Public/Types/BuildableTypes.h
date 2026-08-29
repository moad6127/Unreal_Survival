// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuildableTypes.generated.h"

class ABuildableMaster;
class UStaticMesh;

USTRUCT(BlueprintType)
struct FBuildableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildableMaster> BuildableActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanOnlyBePlacedAtSnappingPoints = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle LinkedInventoryItem;
};