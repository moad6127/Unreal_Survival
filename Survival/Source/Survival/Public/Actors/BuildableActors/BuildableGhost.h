// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableGhost.generated.h"

UCLASS()
class SURVIVAL_API ABuildableGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildableGhost();
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<USceneComponent> BuildableRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<UStaticMeshComponent> BuildableStaticMesh;

};
