// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Respawn/ExtenedRespawnComponent.h"
#include "RespawnComponent.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API URespawnComponent : public UExtenedRespawnComponent
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;

	virtual void Client_InitRespawnUI_Implementation() override;
	virtual void Server_SpawnPlayer_Implementation() override;

	UFUNCTION()
	void HandleOnDeath();

	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<UUserWidget> RespawnWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> RespawnWidgetInstance;
};
