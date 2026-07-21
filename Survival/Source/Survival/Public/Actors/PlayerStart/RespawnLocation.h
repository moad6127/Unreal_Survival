// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "RespawnLocation.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ARespawnLocation : public APlayerStart
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Respawn")
	FTransform GetRespawnTransform() const;

};
