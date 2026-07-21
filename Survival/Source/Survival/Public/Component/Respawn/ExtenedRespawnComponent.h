// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedRespawnComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedRespawnComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client,Reliable)
	void Client_InitRespawnUI();

	UFUNCTION(Server,Reliable)
	void Server_SpawnPlayer();
		
};
