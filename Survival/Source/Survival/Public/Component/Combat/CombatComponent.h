// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/ExtenedCombatComponent.h"
#include "CombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UCombatComponent : public UExtenedCombatComponent
{
	GENERATED_BODY()
	
protected:
	virtual void TryMeleeDamage() override;


	void ProcessHits(const TArray<FHitResult>& Hits);
	void ApplyDamageToActor(AActor* TargetActor, const FHitResult& Hit);

	// 트레이스 시작 위치를 캐릭터 앞으로 밀어주는 오프셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float ForwardOffset = 35.f;

	// 오프셋된 시작점에서 얼마나 더 앞으로 트레이스할지
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float TraceRange = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FVector BoxHalfSize = FVector(150.f, 30.f, 100.f);

	// 데미지 판정 대상으로 삼을 오브젝트 타입들 (Pawn, Damageable 등). 에디터에서 지정.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TArray<TEnumAsByte<EObjectTypeQuery>> DamageObjectTypes;

};
