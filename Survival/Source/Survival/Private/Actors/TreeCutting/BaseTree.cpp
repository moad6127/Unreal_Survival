// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TreeCutting/BaseTree.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ABaseTree::ABaseTree()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);


	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh "));
	SetRootComponent(SceneRoot);

	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BaseMesh->SetCollisionObjectType(ECC_GameTraceChannel2);
	BaseMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BaseMesh->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Block);
	BaseMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	/*
	* 쓰러질 때 분리되는 조각. 평소엔 숨김
	*/
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetupAttachment(SceneRoot);
	ProceduralMesh->SetVisibility(false);

	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProceduralMesh->SetCollisionObjectType(ECC_WorldStatic);
	ProceduralMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ProceduralMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore); // 팜/캐릭터에 부딪혀 튕기는 것 방지
	ProceduralMesh->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	ProceduralMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore); // 쪼개진 조각은 추가 데미지 불필요
	ProceduralMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	ProceduralMesh->SetMassOverrideInKg(NAME_None, 300.f, true);
	ProceduralMesh->bReplicatePhysicsToAutonomousProxy = false;


	ProceduralMeshCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProceduralMeshCollision"));
	ProceduralMeshCollision->SetupAttachment(ProceduralMesh);

	ProceduralMeshCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProceduralMeshCollision->SetCollisionObjectType(ECC_WorldStatic);
	ProceduralMeshCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ProceduralMeshCollision->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Ignore);
	ProceduralMeshCollision->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	ProceduralMeshCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	LogSpawnPoint1 = CreateDefaultSubobject<USceneComponent>(TEXT("LogSpawnPoint1"));
	LogSpawnPoint1->SetupAttachment(ProceduralMesh);

	LogSpawnPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("LogSpawnPoint2"));
	LogSpawnPoint2->SetupAttachment(ProceduralMesh);

	LogSpawnPoint3 = CreateDefaultSubobject<USceneComponent>(TEXT("LogSpawnPoint3"));
	LogSpawnPoint3->SetupAttachment(ProceduralMesh);
}

void ABaseTree::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (StaticMeshTree)
	{
		BaseMesh->SetStaticMesh(StaticMeshTree);
	}
}

void ABaseTree::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void ABaseTree::Initialize()
{
	if (StaticMeshTree)
	{
		BaseMesh->SetStaticMesh(StaticMeshTree);
	}
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(
		BaseMesh, /*LODIndex=*/0, ProceduralMesh, /*bCreateCollision=*/true);

	if (BaseMesh->GetMaterial(ChoppableMaterialIndex))
	{
		OriginalMaterial = BaseMesh->GetMaterial(ChoppableMaterialIndex);
		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
		BaseMesh->SetMaterial(ChoppableMaterialIndex, DynamicMaterialInstance);
	}
}
