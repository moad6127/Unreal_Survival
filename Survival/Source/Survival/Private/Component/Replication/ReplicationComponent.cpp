// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Replication/ReplicationComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"


void UReplicationComponent::Client_InitializeMulticastMontage_Implementation(UAnimMontage* Montage)
{
	PlayMontage(Montage);
	Server_PlayMontage(Montage);
}

void UReplicationComponent::Client_InitializeStopMulticastMontage_Implementation()
{
}

void UReplicationComponent::Client_InitializeSpawnSoundAtLocation_Implementation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings)
{
	SpawnSoundAtLocation(Sound, Location, AttenuationSettings);
	Server_SpawnSoundAtLocation(Sound, Location, AttenuationSettings);
}

void UReplicationComponent::PlayMontage(UAnimMontage* Montage)
{
	if (!Montage)
	{
		return;
	}
	if (UAnimInstance* AnimInstance = GetOwnerAnimInstance())
	{
		AnimInstance->Montage_Play(Montage);
	}
}

void UReplicationComponent::Server_PlayMontage_Implementation(UAnimMontage* Montage)
{
	Multicast_MontageToAllClients(Montage);
}

void UReplicationComponent::Multicast_MontageToAllClients_Implementation(UAnimMontage* Montage)
{
	const ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
	if (OwningCharacter && OwningCharacter->IsLocallyControlled())
	{
		return;
	}
	PlayMontage(Montage);
}



void UReplicationComponent::SpawnSoundAtLocation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings)
{
	if (!Sound)
	{
		return;
	}
	UGameplayStatics::SpawnSoundAtLocation(this,
		Sound,
		Location,
		FRotator::ZeroRotator,
		1.f,
		1.f,
		0.f,
		AttenuationSettings);
}

void UReplicationComponent::Server_SpawnSoundAtLocation_Implementation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings)
{
	Multicast_SpawnSoundAtLocation(Sound, Location, AttenuationSettings);
}

void UReplicationComponent::Multicast_SpawnSoundAtLocation_Implementation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings)
{
	const ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
	if (OwningCharacter && OwningCharacter->IsLocallyControlled())
	{
		return;
	}
	SpawnSoundAtLocation(Sound, Location, AttenuationSettings);
}

