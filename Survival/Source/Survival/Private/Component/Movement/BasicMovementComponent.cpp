// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Movement/BasicMovementComponent.h"
#include "Utils/SurvivalStatics.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UBasicMovementComponent::UBasicMovementComponent()
{

}

void UBasicMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		OwnerPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UBasicMovementComponent::HandleControllerChanged);
		if (AController* CurrentController = OwnerPawn->GetController())
		{
			HandleControllerChanged(OwnerPawn, nullptr, CurrentController);
		}
	}
}

void UBasicMovementComponent::HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	APlayerController* PC = Cast<APlayerController>(NewController);
	if (!IsValid(PC))
	{
		return;
	}

	USurvivalStatics::LinkInputMappingContext(PC, MovementMappingContext, 0);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}
	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UBasicMovementComponent::Move);
	}
	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UBasicMovementComponent::Look);
	}
	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UBasicMovementComponent::Input_JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UBasicMovementComponent::Input_JumpStopped);
	}
	FInputModeGameOnly InputMode;
	PC->SetInputMode(InputMode);
}

void UBasicMovementComponent::Move(const FInputActionValue& Value)
{
	if (DisableMovement)
	{
		return;
	}
	ACharacter* Character = USurvivalStatics::GetCharacterFromComponent(this);
	if (!IsValid(Character))
	{
		return;
	}
	const AController* Controller = Character->GetController();
	if (!IsValid(Controller))
	{
		return;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);


	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Character->AddMovementInput(ForwardDirection, MovementVector.Y);
	Character->AddMovementInput(RightDirection, MovementVector.X);
}

void UBasicMovementComponent::Look(const FInputActionValue& Value)
{
	if (DisableMovement)
	{
		return;
	}
	ACharacter* Character = USurvivalStatics::GetCharacterFromComponent(this);
	if (!IsValid(Character))
	{
		return;
	}

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	Character->AddControllerYawInput(LookAxisVector.X);
	Character->AddControllerPitchInput(LookAxisVector.Y);
}

void UBasicMovementComponent::Input_JumpStarted()
{
	if (DisableMovement)
	{
		return;
	}

	ACharacter* Character = USurvivalStatics::GetCharacterFromComponent(this);
	if (!IsValid(Character))
	{
		return;
	}
	Character->Jump();
}

void UBasicMovementComponent::Input_JumpStopped()
{
	if (DisableMovement)
	{
		return;
	}

	ACharacter* Character = USurvivalStatics::GetCharacterFromComponent(this);
	if (!IsValid(Character))
	{
		return;
	}
	Character->StopJumping();
}
