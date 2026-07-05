// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Survival_MainMenuHUD.generated.h"

/**
 * 
 */
class UUserWidget;


UCLASS()
class SURVIVAL_API ASurvival_MainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitUI();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidget;
};
