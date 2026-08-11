// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EquipActor/EquipActor.h"
#include "Components/StaticMeshComponent.h"
AEquipActor::AEquipActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	SetRootComponent(EquipmentMesh);
}

void AEquipActor::BeginPlay()
{
	Super::BeginPlay();
	
}



