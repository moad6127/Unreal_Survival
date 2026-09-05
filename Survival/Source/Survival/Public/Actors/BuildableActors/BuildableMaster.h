// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/BuildableTypes.h"
#include "BuildableMaster.generated.h"


UCLASS()
class SURVIVAL_API ABuildableMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildableMaster();


	// Location에서 가장 가까운, SnapTargetTag에 해당하는 스냅 포인트를 찾음
	bool GetNearestSnappingPointTransform(const FVector& Location, FName SnapTargetTag, FTransform& OutTransform) const;

	UPROPERTY(EditDefaultsOnly, Category = "Buildable|Snapping")
	FName SnapTagName = NAME_None;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buildable|Snapping")
	TArray<FName> AcceptedSnappingTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildable", meta = (ExposeOnSpawn = "true"))
	FDataTableRowHandle BuildableDataRow;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	void StoreAllSnappingTransforms();
	TArray<FTransform> GetTransformsWithTag(FName Tag) const;
	static bool GetNearestTransform(const TArray<FTransform>& Transforms, const FVector& Location, FTransform& OutTransform);

	UPROPERTY()
	TMap<FName, FSnapTransforms> SnappingTransformsMap;

	// 여러 메시(더블 도어 등)를 담을 수 있는 루트 컨테이너
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<USceneComponent> BuildableRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<UStaticMeshComponent> BuildableStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<USceneComponent> BuildableCollisionRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<USceneComponent> SnapPointsRoots;

private:
	const FBuildableData* GetBuildableData() const;

};
