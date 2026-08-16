// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EquipActor/EquipActor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

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

void AEquipActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEquipActor, EquipmentInfo);
}

void AEquipActor::TryPrimaryAction()
{
	switch (EquipmentInfo.Generic.EquipmentType)
	{
	case EEquipmentType::Hatchet:
		UE_LOG(LogTemp, Log, TEXT("Action on Hatchet"));
		TryMeleeAction();
		break;
	case EEquipmentType::Sword:
		UE_LOG(LogTemp, Log, TEXT("Action on Sword"));
		TryMeleeAction();
		break;
	default:
		break;
	}
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

void AEquipActor::TryMeleeAction()
{
}



