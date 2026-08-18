// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/ExtenedCombatComponent.h"

UExtenedCombatComponent::UExtenedCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UExtenedCombatComponent::Server_TryMeleeDamage_Implementation()
{
	TryMeleeDamage();
}


void UExtenedCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UExtenedCombatComponent::TryMeleeDamage()
{
}

