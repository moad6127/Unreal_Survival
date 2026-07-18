// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/AttributeManager/ExtendedAttributeComponent.h"
#include "AttributeComponent.generated.h"

/**
 * 
 */

UCLASS()
class SURVIVAL_API UAttributeComponent : public UExtendedAttributeComponent
{
	GENERATED_BODY()
	
public:


protected:

	virtual void BeginPlay() override;

private:
	void InitValues();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyStatDamage();
};
