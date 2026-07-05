// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/InputUIComponent.h"
#include "Utils/SurvivalStatics.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"

void UInputUIComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayerController = USurvivalStatics::GetPlayerControllerFromComponent(this);
	if (!IsValid(OwnerPlayerController))
	{
		return;
	}

	USurvivalStatics::LinkInputMappingContext(OwnerPlayerController, UIMappingContext, 0);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerPlayerController->InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}
	if (OpenAndCloseInGameMenu)
	{
		EnhancedInputComponent->BindAction(OpenAndCloseInGameMenu, ETriggerEvent::Completed, this, &UInputUIComponent::OpenAndCloseInGameMenuClicked);
	}
}

void UInputUIComponent::OpenAndCloseInGameMenuClicked()
{
	if (!InGameMenuWidget)
	{
		/*InGameMenu가 없을경우 새롭게 생성한다.*/
		CreateInGameMenu();
	}

	if (InGameMenuActive)
	{
		//Close
		CloseInGameMenu();
	}
	else
	{
		//Oepn
		OpenInGameMenu();
	}
	InGameMenuActive = !InGameMenuActive;

	UE_LOG(LogTemp, Warning, TEXT("OpenAndCloesInGameMenuClicked"));
}

void UInputUIComponent::CreateInGameMenu()
{
	InGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), InGameMenuWidgetClass);
	InGameMenuWidget->AddToViewport();
	InGameMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UInputUIComponent::OpenInGameMenu()
{
	if (!OwnerPlayerController)
	{
		OwnerPlayerController = USurvivalStatics::GetPlayerControllerFromComponent(this);
	}
	const FInputModeGameAndUI InputMode;
	OwnerPlayerController->SetInputMode(InputMode);
	OwnerPlayerController->SetShowMouseCursor(true);
	InGameMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void UInputUIComponent::CloseInGameMenu()
{
	if (!OwnerPlayerController)
	{
		OwnerPlayerController = USurvivalStatics::GetPlayerControllerFromComponent(this);
	}
	const FInputModeGameOnly InputMode;
	OwnerPlayerController->SetInputMode(InputMode);
	OwnerPlayerController->SetShowMouseCursor(false);
	InGameMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}
