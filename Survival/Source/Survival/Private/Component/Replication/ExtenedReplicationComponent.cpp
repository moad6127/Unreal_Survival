// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Replication/ExtenedReplicationComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

UExtenedReplicationComponent::UExtenedReplicationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UExtenedReplicationComponent::Client_InitializeMulticastMontage_Implementation(UAnimMontage* Montage)
{
}

void UExtenedReplicationComponent::Client_InitializeStopMulticastMontage_Implementation()
{
}


void UExtenedReplicationComponent::Client_InitializeSpawnSoundAtLocation_Implementation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings)
{
}

// Called when the game starts
void UExtenedReplicationComponent::BeginPlay()
{
	Super::BeginPlay();

}

UAnimInstance* UExtenedReplicationComponent::GetOwnerAnimInstance() const
{
	if (const ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* Mesh = OwningCharacter->GetMesh())
		{
			return Mesh->GetAnimInstance();
		}
	}
	return nullptr;
}


