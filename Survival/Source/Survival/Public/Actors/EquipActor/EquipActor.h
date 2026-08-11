// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipActor.generated.h"

UCLASS()
class SURVIVAL_API AEquipActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UStaticMeshComponent> EquipmentMesh;
};
