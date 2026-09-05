// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BuildableActors/BuildableMaster.h"
#include "Components/StaticMeshComponent.h"


ABuildableMaster::ABuildableMaster()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

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

bool ABuildableMaster::GetNearestSnappingPointTransform(const FVector& Location, FName SnapTargetTag, FTransform& OutTransform) const
{
	const FSnapTransforms* SnapTransforms = SnappingTransformsMap.Find(SnapTargetTag);

	if (!SnapTransforms || SnapTransforms->Transforms.Num() == 0)
	{
		return false;
	}

	return GetNearestTransform(SnapTransforms->Transforms, Location, OutTransform);
}

void ABuildableMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (const FBuildableData* Data = GetBuildableData())
	{
		BuildableStaticMesh->SetStaticMesh(Data->Mesh);
	}
}

void ABuildableMaster::BeginPlay()
{
	Super::BeginPlay();
	StoreAllSnappingTransforms();
}

void ABuildableMaster::StoreAllSnappingTransforms()
{
	SnappingTransformsMap.Empty();

	for (const FName& Tag : AcceptedSnappingTags)
	{
		TArray<FTransform> Found = GetTransformsWithTag(Tag);
		if (Found.Num() > 0)
		{
			FSnapTransforms SnapTransforms;
			SnapTransforms.Transforms = MoveTemp(Found);
			SnappingTransformsMap.Add(Tag, SnapTransforms);
		}
	}
}

TArray<FTransform> ABuildableMaster::GetTransformsWithTag(FName Tag) const
{
	TArray<FTransform> FoundTransforms;

	TArray<UActorComponent*> TaggedComponents = GetComponentsByTag(USceneComponent::StaticClass(), Tag);
	for (UActorComponent* Component : TaggedComponents)
	{
		if (const USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
		{
			FoundTransforms.Add(SceneComponent->GetComponentTransform());
		}
	}

	return FoundTransforms;
}

bool ABuildableMaster::GetNearestTransform(const TArray<FTransform>& Transforms, const FVector& Location, FTransform& OutTransform)
{
	if (Transforms.Num() == 0)
	{
		return false;
	}

	OutTransform = Transforms[0];
	float NearestDistSq = FVector::DistSquared(Location, OutTransform.GetLocation());

	for (int32 Index = 1; Index < Transforms.Num(); ++Index)
	{
		const float DistSq = FVector::DistSquared(Location, Transforms[Index].GetLocation());
		if (DistSq < NearestDistSq)
		{
			NearestDistSq = DistSq;
			OutTransform = Transforms[Index];
		}
	}

	return true;
}

const FBuildableData* ABuildableMaster::GetBuildableData() const
{
	if (!BuildableDataRow.DataTable)
	{
		return nullptr;
	}

	return BuildableDataRow.GetRow<FBuildableData>(TEXT("ABuildableMaster::GetBuildableData"));
}



