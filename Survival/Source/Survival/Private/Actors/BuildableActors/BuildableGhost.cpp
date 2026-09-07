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
	BuildableStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BuildableStaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	BuildableStaticMesh->SetGenerateOverlapEvents(true);
}

void ABuildableGhost::SetGhostMeshMaterial(UMaterialInterface* Material)
{
	if (!Material || !BuildableStaticMesh)
	{
		return;
	}

	const int32 NumMaterials = BuildableStaticMesh->GetNumMaterials();
	for (int32 Index = 0; Index < NumMaterials; ++Index)
	{
		BuildableStaticMesh->SetMaterial(Index, Material);
	}
}

void ABuildableGhost::SetCanBuild(bool bCanBuild)
{
	SetGhostMeshMaterial(bCanBuild ? GreenGlassMaterial : RedGlassMaterial);
}

bool ABuildableGhost::IsOverlappingBuildable() const
{
	if (!BuildableStaticMesh)
	{
		return false;
	}

	TArray<UPrimitiveComponent*> OverlappingComponents;
	BuildableStaticMesh->GetOverlappingComponents(OverlappingComponents);

	UE_LOG(LogTemp, Log, TEXT("Overlapping component count: %d"), OverlappingComponents.Num());

	for (const UPrimitiveComponent* Component : OverlappingComponents)
	{
		if (!Component)
		{
			continue;
		}

		UE_LOG(LogTemp, Log, TEXT("  - %s (HasTag: %d)"), *Component->GetName(), Component->ComponentHasTag("BuildableOverlap"));

		if (Component->ComponentHasTag("BuildableOverlap"))
		{
			return true;
		}
	}
	return false;
}

void ABuildableGhost::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (const FBuildableData* Data = GetBuildableData())
	{
		BuildableStaticMesh->SetStaticMesh(Data->Mesh);
	}
}

void ABuildableGhost::BeginPlay()
{
	Super::BeginPlay();

	SetGhostMeshMaterial(WhiteGlassMaterial);
}

const FBuildableData* ABuildableGhost::GetBuildableData() const
{
	if (!BuildableDataRow.DataTable)
	{
		return nullptr;
	}
	return BuildableDataRow.GetRow<FBuildableData>(TEXT("ABuildableGhost::GetBuildableData"));
}
