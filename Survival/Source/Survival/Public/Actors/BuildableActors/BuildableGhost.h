// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/BuildableTypes.h"
#include "BuildableGhost.generated.h"

UCLASS()
class SURVIVAL_API ABuildableGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildableGhost();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildable", meta = (ExposeOnSpawn = "true"))
	FDataTableRowHandle BuildableDataRow;

	void SetGhostMeshMaterial(UMaterialInterface* Material);
	void SetCanBuild(bool bCanBuild);
	bool IsOverlappingBuildable() const;
protected:

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<USceneComponent> BuildableRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<UStaticMeshComponent> BuildableStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Buildable|Ghost")
	TObjectPtr<UMaterialInterface> GreenGlassMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Buildable|Ghost")
	TObjectPtr<UMaterialInterface> RedGlassMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Buildable|Ghost")
	TObjectPtr<UMaterialInterface> WhiteGlassMaterial;

private:
	const FBuildableData* GetBuildableData() const;
};
