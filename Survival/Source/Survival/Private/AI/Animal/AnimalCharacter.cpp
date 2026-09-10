// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animal/AnimalCharacter.h"
#include "Net/UnrealNetwork.h"


AAnimalCharacter::AAnimalCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AAnimalCharacter::SetIdleAction(EAnimalIdleAction NewAction)
{
	if (!HasAuthority())
	{
		return;
	}

	CurrentIdleAction = NewAction;
}

void AAnimalCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAnimalCharacter, CurrentIdleAction);
}
