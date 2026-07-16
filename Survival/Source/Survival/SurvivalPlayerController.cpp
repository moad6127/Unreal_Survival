// Copyright Epic Games, Inc. All Rights Reserved.


#include "SurvivalPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Survival.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "Utils/SurvivalStatics.h"
#include "HUD/Survival_HUD.h"

UAttributeComponent* ASurvivalPlayerController::GetAttributeManager()
{
	return USurvivalStatics::GetComponentFromController<UAttributeComponent>(this);
}

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogSurvival, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ASurvivalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

void ASurvivalPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (ASurvival_HUD* SurvivalHUD = GetHUD<ASurvival_HUD>())
	{
		SurvivalHUD->InitInGameHUD(this);
	}
}

bool ASurvivalPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
