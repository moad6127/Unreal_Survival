// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SurvivalStatics.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

UEnhancedInputLocalPlayerSubsystem* USurvivalStatics::GetEnhancedInputSubsystem(APlayerController* PlayerController)
{
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Warning, TEXT("USurvivalStatics: PlayerController is null."));
		return nullptr;
	}
	if (!IsValid(PlayerController->GetLocalPlayer()))
	{
		UE_LOG(LogTemp, Warning, TEXT("USurvivalStatics: LocalPlayer is null."));

		return nullptr;
	}
	return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
}

void USurvivalStatics::LinkInputMappingContext(APlayerController* PlayerController, UInputMappingContext* MappingContext, int32 Priority)
{
	if (!IsValid(MappingContext))
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* SubSystem = GetEnhancedInputSubsystem(PlayerController);
	if (!SubSystem)
	{
		return;
	}
	SubSystem->AddMappingContext(MappingContext, Priority);
}

void USurvivalStatics::UnlinkInputMappingContext(APlayerController* PlayerController, UInputMappingContext* MappingContext)
{
	if (!IsValid(MappingContext))
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* SubSystem = GetEnhancedInputSubsystem(PlayerController);
	if (!SubSystem)
	{
		return;
	}
	SubSystem->RemoveMappingContext(MappingContext);
}

void USurvivalStatics::SwitchInputMappingContext(APlayerController* PlayerController, UInputMappingContext* OldMappingContext, UInputMappingContext* NewMappingContext, int32 Priority)
{
	UnlinkInputMappingContext(PlayerController, OldMappingContext);
	LinkInputMappingContext(PlayerController, NewMappingContext, Priority);
}
