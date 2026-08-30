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

	BuildableCollisionRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BuildableCollisionRoot"));
	BuildableCollisionRoot->SetupAttachment(BuildableRoot);

	SnapPointsRoots = CreateDefaultSubobject<USceneComponent>(TEXT("SnapPointsRoots"));
	SnapPointsRoots->SetupAttachment(BuildableRoot);

	AcceptedSnappingTags = { TEXT("Foundation"), TEXT("Wall"), TEXT("Ceiling"), TEXT("Ramp") };
}

void ABuildableMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (const FBuildableData* Data = GetBuildableData())
	{
		BuildableStaticMesh->SetStaticMesh(Data->Mesh);
	}
}

const FBuildableData* ABuildableMaster::GetBuildableData() const
{
	if (!BuildableDataRow.DataTable)
	{
		return nullptr;
	}

	return BuildableDataRow.GetRow<FBuildableData>(TEXT("ABuildableMaster::GetBuildableData"));
}



