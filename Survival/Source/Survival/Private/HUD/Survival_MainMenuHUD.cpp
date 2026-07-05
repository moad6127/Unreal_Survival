// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Survival_MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASurvival_MainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}

void ASurvival_MainMenuHUD::InitUI()
{
	MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
	if (MainMenuWidget)
	{
		const FInputModeUIOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
		MainMenuWidget->AddToViewport();
	}
}
