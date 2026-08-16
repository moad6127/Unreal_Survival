// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/EquipmentTypes.h"
#include "EquipActor.generated.h"

UCLASS()
class SURVIVAL_API AEquipActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipActor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FEquipmentItem EquipmentInfo;

	void TryPrimaryAction();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<USceneComponent> EquipmentRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UStaticMeshComponent> EquipmentMesh;

	void Initialize();

	void TryMeleeAction();
};
