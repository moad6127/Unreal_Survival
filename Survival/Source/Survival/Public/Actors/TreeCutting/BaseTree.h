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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnConstruction(const FTransform& Transform) override;
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Tree")
	void Initialize();

	UFUNCTION()
	void OnRep_DamagedCursor();

	UFUNCTION()
	void OnRep_CurrentOffset();

	UFUNCTION(Server, Reliable)
	void Server_InitializeMask(AActor* InDamageCauser);

	UFUNCTION(Server, Reliable)
	void Server_ProcessHit();

	UFUNCTION(BlueprintCallable, Category = "Tree")
	void SplitTree();

	void ApplyInitialMask(AActor* InDamagedCursor);

	void ApplyMaskAlpha();


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
	float MaxOffset = 0.75f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Configuration")
	float DamageIncrement = 0.15f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentOffset, BlueprintReadOnly, Category = "Tree")
	float CurrentOffset = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Tree")
	bool bIsTreeBroken = false;

	UPROPERTY(ReplicatedUsing = OnRep_DamagedCursor)
	TObjectPtr<AActor> DamagedCursor;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> OriginalMaterial;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	bool bMaskInitialized = false;

	// --- 마스크 관련 파라미터 (Configuration에서 오버라이드 가능) ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	FName StartLocationParamName = TEXT("StartLocation");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	FName InsideTilingParamName = TEXT("Inside_Tiling");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	FName EdgeFalloffParamName = TEXT("Edge_Fallof");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	FName MaskBoundsParamName = TEXT("Bounds");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	float MaskHeight = 115.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	float InsideTiling = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	float EdgeFalloff = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree|Mask")
	FVector MaskBounds = FVector(150.f, 150.f, 50.f);
};
