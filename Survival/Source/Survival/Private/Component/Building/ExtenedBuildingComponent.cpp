// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Building/ExtenedBuildingComponent.h"

UExtenedBuildingComponent::UExtenedBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

}

void UExtenedBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UExtenedBuildingComponent::StartBuildMode(const FInventoryItemSlot& ItemSlot)
{
}

void UExtenedBuildingComponent::StopBuildMode()
{
}




