// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTree.generated.h"

class UProceduralMeshComponent;
class UCapsuleComponent;
class UMaterialInstanceDynamic;

UCLASS()
class SURVIVAL_API ABaseTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTree();

	virtual void OnConstruction(const FTransform& Transform) override;
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Tree")
	void Initialize();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UProceduralMeshComponent> ProceduralMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UCapsuleComponent> ProceduralMeshCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<USceneComponent> LogSpawnPoint1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<USceneComponent> LogSpawnPoint2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<USceneComponent> LogSpawnPoint3;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Configuration")
	TObjectPtr<UStaticMesh> StaticMeshTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Configuration")
	int32 ChoppableMaterialIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Configuration")
	FName OffsetMaskParamName = TEXT("OffsetMask");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Configuration")
	float MaxOffset = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Configuration")
	float DamageIncrement = 0.1f;

	UPROPERTY(BlueprintReadOnly, Category = "Tree")
	float CurrentOffset = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInterface> OriginalMaterial;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;
};
