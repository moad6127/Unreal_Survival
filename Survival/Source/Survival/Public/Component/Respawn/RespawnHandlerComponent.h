// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnHandlerComponent.generated.h"

class ARespawnLocation;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API URespawnHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URespawnHandlerComponent();

	UFUNCTION(BlueprintCallable, Category = "Respawn")
	void SpawnPlayer(APlayerController* PlayerController, ARespawnLocation* RespawnLocation);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<ACharacter> PlayerClassToSpawn;
		
};
