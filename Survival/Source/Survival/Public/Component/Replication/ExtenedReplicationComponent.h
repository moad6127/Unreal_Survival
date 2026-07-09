// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedReplicationComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedReplicationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedReplicationComponent();


	// 소유 클라이언트에서 몽타주 재생을 시작하는 진입점.
	UFUNCTION(Client, Unreliable, BlueprintCallable, Category = "Replication|Montage")
	void Client_InitializeMulticastMontage(UAnimMontage* Montage);

	UFUNCTION(Client, Unreliable, BlueprintCallable, Category = "Replication|Montage")
	void Client_InitializeStopMulticastMontage();

	// 소유 클라이언트에서 몽타주 재생을 시작하는 진입점.
	UFUNCTION(Client, Unreliable, BlueprintCallable, Category = "Replication|Sound")
	void Client_InitializeSpawnSoundAtLocation(USoundBase* Sound, FVector Location, USoundAttenuation* AttenuationSettings);

protected:
	virtual void BeginPlay() override;

	UAnimInstance* GetOwnerAnimInstance() const;
};
