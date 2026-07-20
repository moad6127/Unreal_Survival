// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Ragdoll/ExtenedRagdollComponent.h"
#include "Net/UnrealNetwork.h"

UExtenedRagdollComponent::UExtenedRagdollComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UExtenedRagdollComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UExtenedRagdollComponent, bRagdolling);
}

void UExtenedRagdollComponent::Server_Ragdoll_Implementation(bool NewRagdolling)
{
	if (bRagdolling)
	{
		return;
	}

	bRagdolling = true;
	OnRep_bRagdolling();
}


void UExtenedRagdollComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UExtenedRagdollComponent::OnRep_bRagdolling()
{
	if (bRagdolling)
	{
		ToRagdoll();
	}
}

void UExtenedRagdollComponent::ToRagdoll()
{
}

