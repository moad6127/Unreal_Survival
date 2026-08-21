// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTree.generated.h"

UCLASS()
class SURVIVAL_API ABaseTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTree();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UStaticMeshComponent> TreeMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree")
	float MaxOffset = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tree")
	float DamageIncrement = 0.1f;

	UPROPERTY(BlueprintReadOnly, Category = "Tree")
	float CurrentOffset = 0.f;
};
