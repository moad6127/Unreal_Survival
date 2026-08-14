// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EquipActor/EquipActor.h"
#include "Components/StaticMeshComponent.h"
AEquipActor::AEquipActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	EquipmentRoot = CreateDefaultSubobject<USceneComponent>(TEXT("EquipmentRoot"));
	SetRootComponent(EquipmentRoot);


	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	EquipmentMesh->SetupAttachment(EquipmentRoot);

	EquipmentMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EquipmentMesh->SetCollisionObjectType(ECC_WorldDynamic);
	EquipmentMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	EquipmentMesh->SetGenerateOverlapEvents(false);
	EquipmentMesh->SetCanEverAffectNavigation(false);
	EquipmentMesh->CanCharacterStepUpOn = ECB_No;
}

void AEquipActor::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
}

void AEquipActor::Initialize()
{
	if (EquipmentMesh)
	{
		EquipmentMesh->SetStaticMesh(EquipmentInfo.Equip.Mesh);
	}
}



