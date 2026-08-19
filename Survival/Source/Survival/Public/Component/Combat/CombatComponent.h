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
};
