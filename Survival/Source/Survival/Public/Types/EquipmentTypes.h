// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EquipmentTypes.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	Default,
	Hatchet,
	Sword
	// 필요할 때 Firearm, Pistol, Rifle, Spear, Pickaxe 등 추가
};

//새롭게 커스텀을 만들어서 사용하기
USTRUCT(BlueprintType)
struct FCustomTransform
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Scale = FVector::OneVector;

	FTransform ToTransform() const
	{
		return FTransform(Rotation, Location, Scale);
	}
};

USTRUCT(BlueprintType)
struct FEquipmentAttributeGeneric
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEquipmentType EquipmentType = EEquipmentType::Default;

	// 언이큅했을 때 되돌려줄 인벤토리 아이템
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle LinkedInventoryItem;
};

USTRUCT(BlueprintType)
struct FEquipmentAttributeEquip
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	// 케이스 센시티브. 스켈레탈 메시에 만들어둔 소켓 이름과 정확히 일치해야 함 (예: weapon_r)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SocketName = "HandGrip_R";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCustomTransform SocketOffset;
};

USTRUCT(BlueprintType)
struct FEquipmentAttributeMelee
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHasMelee = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHasMelee"))
	TObjectPtr<UAnimMontage> MeleeMontage = nullptr;
};

// DT_Equipment 데이터 테이블의 Row Struct
USTRUCT(BlueprintType)
struct FEquipmentItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEquipmentAttributeGeneric Generic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEquipmentAttributeEquip Equip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEquipmentAttributeMelee Melee;
};