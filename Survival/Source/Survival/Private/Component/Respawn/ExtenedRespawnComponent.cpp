// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Respawn/ExtenedRespawnComponent.h"

UExtenedRespawnComponent::UExtenedRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}


void UExtenedRespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UExtenedRespawnComponent::Client_InitRespawnUI_Implementation()
{
}

void UExtenedRespawnComponent::Server_SpawnPlayer_Implementation()
{
}

