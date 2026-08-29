// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BuildableActors/BuildableGhost.h"

// Sets default values
ABuildableGhost::ABuildableGhost()
{
	PrimaryActorTick.bCanEverTick = false;

	BuildableRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BuildableRoot"));
	RootComponent = BuildableRoot;

	BuildableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildableStaticMesh"));
	BuildableStaticMesh->SetupAttachment(BuildableRoot);
}

