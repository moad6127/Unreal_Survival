// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Interaction/InteractionComponent.h"
#include "Utils/SurvivalStatics.h"
#include "EnhancedInputComponent.h"

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerPlayerController = USurvivalStatics::GetPlayerControllerFromComponent(this);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (IsValid(OwnerPlayerController) && IsValid(OwnerPawn) && OwnerPawn->IsLocallyControlled())
	{
		InitInput();
	}
}

void UInteractionComponent::InitInput()
{

	USurvivalStatics::LinkInputMappingContext(OwnerPlayerController, InteractContext, 0);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerPlayerController->InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}
	/*	
	if (InteractContext)
	{
		EnhancedInputComponent->BindAction(InteractContext, ETriggerEvent::Completed, this, &UInteractionComponent::SomeFunc);
	}
	*/
	StartCanInteractTrace();
}

void UInteractionComponent::StartCanInteractTrace()
{
	GetWorld()->GetTimerManager().SetTimer(
		TraceTimer,
		this,
		&UInteractionComponent::LineTraceInteraction,
		TimerRate,
		true);
}

void UInteractionComponent::LineTraceInteraction()
{
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	bool bHit = USurvivalStatics::TraceFromActiveCamera(
		OwnerPlayerController,
		InteractTraceChannel,
		ActorsToIgnore,
		FrontOffsetStartPosition,
		TraceLength,
		Hit);
	if (bHit)
	{
		HandleInteraction(Hit.GetActor());
	}
}

void UInteractionComponent::HandleInteraction(AActor* HitActor)
{
}
