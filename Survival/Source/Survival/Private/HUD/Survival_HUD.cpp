// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Survival_HUD.h"
#include "Blueprint/UserWidget.h"


void ASurvival_HUD::BeginPlay()
{
	Super::BeginPlay();

}

void ASurvival_HUD::InitInGameHUD(APlayerController* OwningController)
{
    if (!IsValid(OwningController) || !InGameHUDWidgetClass)
    {
        return;
    }

    // 이미 생성되어 있으면 재생성하지 않음 (재초기화 대비 멱등성 유지)

    if (!IsValid(InGameHUDWidget))
    {
        InGameHUDWidget = CreateWidget<UUserWidget>(OwningController, InGameHUDWidgetClass);
        if (!InGameHUDWidget)
        {
            return;
        }
        InGameHUDWidget->AddToViewport(0);
    }

    FInputModeGameOnly InputMode;
    OwningController->SetInputMode(InputMode);
    OwningController->SetShowMouseCursor(false);
}
