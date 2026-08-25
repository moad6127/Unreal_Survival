// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TreeCutting/BaseTree.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "Utils/EquipmentStatics.h"
#include "Utils/SurvivalStatics.h"
#include "Component/Equipment/ExtenedEquipmentComponent.h"
#include "Types/EquipmentTypes.h"

ABaseTree::ABaseTree()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(GetRootComponent());

	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BaseMesh->SetCollisionObjectType(ECC_GameTraceChannel2);
	BaseMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BaseMesh->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Block);
	BaseMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	/*
	* 쓰러질 때 분리되는 조각. 평소엔 숨김
	*/
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetupAttachment(GetRootComponent());
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

void ABaseTree::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseTree, DamagedCursor);
	DOREPLIFETIME(ABaseTree, CurrentOffset);
}

void ABaseTree::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!BaseMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("[BaseTree] OnConstruction: BaseMesh is NULL on %s"), *GetName());
		return;
	}

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
	if (!BaseMesh || !ProceduralMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("[BaseTree] Initialize aborted: BaseMesh or ProceduralMesh is NULL on %s"), *GetName());
		return;
	}

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


float ABaseTree::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!HasAuthority() || bIsTreeBroken)
	{
		return AppliedDamage;
	}

	if (!EventInstigator)
	{
		return AppliedDamage;
	}

	UExtenedEquipmentComponent* EquipmentComp = USurvivalStatics::GetComponentFromController<UExtenedEquipmentComponent>(EventInstigator);
	if (!EquipmentComp)
	{
		return AppliedDamage;
	}

	FEquipmentItem EquipmentInfo;
	if (!UEquipmentStatics::GetEquipmentInfoFromInventorySlot(EquipmentComp->GetEquipmentSlot(), EquipmentInfo))
	{
		return AppliedDamage;
	}

	if (EquipmentInfo.Generic.EquipmentType != EEquipmentType::Hatchet)
	{
		return AppliedDamage;
	}

	if (!bMaskInitialized)
	{
		bMaskInitialized = true;
		Server_InitializeMask(DamageCauser);
	}

	Server_ProcessHit();

	return AppliedDamage;
}


void ABaseTree::OnRep_DamagedCursor()
{
	ApplyInitialMask(DamagedCursor);
}

void ABaseTree::OnRep_CurrentOffset()
{
	ApplyMaskAlpha();
}

void ABaseTree::Server_InitializeMask_Implementation(AActor* InDamageCauser)
{
	DamagedCursor = InDamageCauser;
	ApplyInitialMask(DamagedCursor);
}

void ABaseTree::Server_ProcessHit_Implementation()
{
	if (bIsTreeBroken)
	{
		return;
	}

	CurrentOffset += DamageIncrement;
	ApplyMaskAlpha(); // 서버 자신은 OnRep을 받지 못하므로 직접 호출

	if (CurrentOffset >= MaxOffset)
	{
		SplitTree();
	}
}

void ABaseTree::SplitTree()
{
}

void ABaseTree::ApplyInitialMask(AActor* InDamagedCursor)
{
	if (!DynamicMaterialInstance || !InDamagedCursor)
	{

		return;
	}
	const FVector CursorLocation = GetActorLocation();
	const FLinearColor StartLocationParam(CursorLocation.X, CursorLocation.Y, CursorLocation.Z + MaskHeight, 0.f);


	DynamicMaterialInstance->SetVectorParameterValue(StartLocationParamName, StartLocationParam);
	DynamicMaterialInstance->SetScalarParameterValue(InsideTilingParamName, InsideTiling);
	DynamicMaterialInstance->SetScalarParameterValue(EdgeFalloffParamName, EdgeFalloff);
	DynamicMaterialInstance->SetVectorParameterValue(
		MaskBoundsParamName, FLinearColor(MaskBounds.X, MaskBounds.Y, MaskBounds.Z, 0.f));
}

void ABaseTree::ApplyMaskAlpha()
{
	if (!DynamicMaterialInstance)
	{
		return;
	}
	DynamicMaterialInstance->SetScalarParameterValue(OffsetMaskParamName, CurrentOffset);

}
