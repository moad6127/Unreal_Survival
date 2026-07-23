// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeType.generated.h"



UENUM(BlueprintType)
enum class EAttributeTypes : uint8
{
	None,
	Health,
	Food,
	Hydration,
	Damage
};

