// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Replication/ExtenedReplicationComponent.h"
#include "ReplicationComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UReplicationComponent : public UExtenedReplicationComponent
{
	GENERATED_BODY()
	
public:
	virtual void Client_InitializeMulticastMontage_Implementation(UAnimMontage* Montage) override;
	virtual void Client_InitializeStopMulticastMontage_Implementation() override;
	virtual void Client_InitializeSpawnSoundAtLocation_Implementation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings) override;
private:

	/*
	* Montage Play
	*/
	void PlayMontage(UAnimMontage* Montage);

	UFUNCTION(Server,Reliable)
	void Server_PlayMontage(UAnimMontage* Montage);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_MontageToAllClients(UAnimMontage* Montage);
	/*
	* Sounds Play
	*/
	void SpawnSoundAtLocation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings);

	UFUNCTION(Server, Unreliable)
	void Server_SpawnSoundAtLocation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_SpawnSoundAtLocation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings);

	UPROPERTY()
	TObjectPtr<UAnimMontage> CurrentActiveMontage;
};
