// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Building/ExtenedBuildingComponent.h"
#include "BuildingComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UBuildingComponent : public UExtenedBuildingComponent
{
	GENERATED_BODY()
public:

	virtual void StartBuildMode(const FInventoryItemSlot& ItemSlot) override;
	virtual void StopBuildMode() override;
};
