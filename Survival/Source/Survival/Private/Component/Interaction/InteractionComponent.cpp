// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Interaction/InteractionComponent.h"
#include "Utils/SurvivalStatics.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/InteractInterface.h"
#include "Interfaces/CanInteractInterface.h"
#include "Component/AttributeManager/AttributeComponent.h"

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		OwnerPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UInteractionComponent::HandleControllerChanged);
		if (AController* CurrentController = OwnerPawn->GetController())
		{
			HandleControllerChanged(OwnerPawn, nullptr, CurrentController);
		}
	}
	if (UAttributeComponent* AttributeComponent = USurvivalStatics::GetComponentFromActor<UAttributeComponent>(GetOwner()))
	{
		AttributeComponent->OnDeath.AddDynamic(this, &UInteractionComponent::HandleInteractOnDeath);
	}
}

void UInteractionComponent::HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	OwnerPlayerController = Cast<APlayerController>(NewController);
	if (IsValid(OwnerPlayerController) && Pawn->IsLocallyControlled())
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

	if (InteractInputAction)
	{
		EnhancedInputComponent->BindAction(InteractInputAction, ETriggerEvent::Started, this, &UInteractionComponent::TargetInteract);
	}

	StartCanInteractTrace();
}

void UInteractionComponent::TargetInteract()
{
	if (!ThisActor.IsValid())
	{
		return;
	}
	if (!ThisActor->Implements<UInteractInterface>())
	{
		return;
	}
	if (!ThisActor->Implements<UCanInteractInterface>())
	{
		return;
	}
	if (ICanInteractInterface::Execute_ShouldExecuteInteractionOnServer(ThisActor.Get()))
	{
		Server_TargetInteract(ThisActor.Get(), OwnerPlayerController);
	}
	else
	{
		IInteractInterface::Execute_Interact(ThisActor.Get(),OwnerPlayerController);
	}
}

void UInteractionComponent::HandleInteractOnDeath()
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimer);
	HandleInteraction(nullptr);
}



void UInteractionComponent::Server_TargetInteract_Implementation(AActor* ActorToInteractWith, AController* InstigatingController)
{
	if (!IsValid(ActorToInteractWith))
	{
		return;
	}
	IInteractInterface::Execute_Interact(ActorToInteractWith, InstigatingController);
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

	HandleInteraction(Hit.GetActor());
}

void UInteractionComponent::HandleInteraction(AActor* HitActor)
{
	LastActor = ThisActor;
	ThisActor = HitActor;

	if (ThisActor == LastActor)
	{
		return;
	}

	if (LastActor.IsValid())
	{
		ICanInteractInterface::Execute_HideInteractPrompt(LastActor.Get());
	}

	if (ThisActor.IsValid() && ThisActor->Implements<UCanInteractInterface>())
	{
		if (ICanInteractInterface::Execute_CanInteract(ThisActor.Get(), OwnerPlayerController))
		{
			ICanInteractInterface::Execute_ShowInteractPrompt(ThisActor.Get());
		}
		else
		{
			ThisActor = nullptr;
		}
	}
	else
	{
		ThisActor = nullptr;
	}
}

