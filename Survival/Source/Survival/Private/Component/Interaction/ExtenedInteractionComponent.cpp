// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Interaction/ExtenedInteractionComponent.h"

UExtenedInteractionComponent::UExtenedInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}


void UExtenedInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

