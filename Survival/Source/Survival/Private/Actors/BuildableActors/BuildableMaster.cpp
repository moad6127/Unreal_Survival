// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BuildableActors/BuildableMaster.h"
#include "Components/StaticMeshComponent.h"

ABuildableMaster::ABuildableMaster()
{
	PrimaryActorTick.bCanEverTick = false;

	BuildableRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BuildableRoot"));
	RootComponent = BuildableRoot;

	BuildableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildableStaticMesh"));
	BuildableStaticMesh->SetupAttachment(BuildableRoot);
}



