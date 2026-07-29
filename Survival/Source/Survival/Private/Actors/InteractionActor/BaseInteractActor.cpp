// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractionActor/BaseInteractActor.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

ABaseInteractActor::ABaseInteractActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(ItemMesh);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);



	/*
	* Widget
	*/

	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComponent"));
	InteractWidgetComponent->SetupAttachment(ItemMesh);
	InteractWidgetComponent->SetUsingAbsoluteRotation(true);
	InteractWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidgetComponent->SetDrawSize(FVector2D(100.f, 50.f));
	InteractWidgetComponent->SetVisibility(false);

	bReplicates = true;
}

void ABaseInteractActor::Interact_Implementation(AController* InstigatorController)
{
	/*
	* 
	*/
}

bool ABaseInteractActor::CanInteract_Implementation(AController* InstigatorController)
{
	return bIsInteractable;
}

FText ABaseInteractActor::GetInteractText_Implementation(AController* InstigatorController)
{
	return InteractText;
}

FVector ABaseInteractActor::GetInteractTextLocation_Implementation()
{
	return InteractTextLocation;
}

bool ABaseInteractActor::ShouldExecuteInteractionOnServer_Implementation()
{
	return bExecuteInteractionOnServer;
}

void ABaseInteractActor::ShowInteractPrompt_Implementation()
{
	InteractWidgetComponent->SetVisibility(true);
}

void ABaseInteractActor::HideInteractPrompt_Implementation()
{
	InteractWidgetComponent->SetVisibility(false);
}

void ABaseInteractActor::BeginPlay()
{
	Super::BeginPlay();

	InteractWidgetComponent->SetRelativeLocation(InteractTextLocation);
}


