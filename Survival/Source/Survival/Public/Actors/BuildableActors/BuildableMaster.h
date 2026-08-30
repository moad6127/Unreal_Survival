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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buildable|Snapping")
	TArray<FName> AcceptedSnappingTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildable", meta = (ExposeOnSpawn = "true"))
	FDataTableRowHandle BuildableDataRow;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

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
