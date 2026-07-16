// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Survival_HUD.generated.h"

/**
 * 
 */
class UUserWidget;
class APlayerController;


UCLASS()
class SURVIVAL_API ASurvival_HUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	void InitInGameHUD(APlayerController* OwningController);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UUserWidget> InGameHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> InGameHUDWidget;
};
