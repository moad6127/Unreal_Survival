// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableMaster.generated.h"

UCLASS()
class SURVIVAL_API ABuildableMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildableMaster();
protected:

	// 여러 메시(더블 도어 등)를 담을 수 있는 루트 컨테이너
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<USceneComponent> BuildableRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildable")
	TObjectPtr<UStaticMeshComponent> BuildableStaticMesh;
};
