// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Respawn/RespawnHandlerComponent.h"
#include "Actors/PlayerStart/RespawnLocation.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


URespawnHandlerComponent::URespawnHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void URespawnHandlerComponent::SpawnPlayer(APlayerController* PlayerController, ARespawnLocation* RespawnLocation)
{
	if (!PlayerController || !RespawnLocation || !PlayerClassToSpawn)
	{
		return;
	}
	if (APawn* ExistingPawn = PlayerController->GetPawn())
	{
		ExistingPawn->Destroy();
	}

	ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(PlayerClassToSpawn, RespawnLocation->GetRespawnTransform());
	if (NewCharacter)
	{
		PlayerController->Possess(NewCharacter);
	}
}


void URespawnHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

