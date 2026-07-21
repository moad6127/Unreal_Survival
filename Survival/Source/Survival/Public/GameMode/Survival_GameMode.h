// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Survival_GameMode.generated.h"

/**
 * 
 */
class URespawnHandlerComponent;


UCLASS()
class SURVIVAL_API ASurvival_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	ASurvival_GameMode();
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URespawnHandlerComponent> RespawnHandlerComponent;
};
