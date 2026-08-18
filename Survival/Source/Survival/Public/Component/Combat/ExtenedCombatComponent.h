// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedCombatComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedCombatComponent();


	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Combat")
	void Server_TryMeleeDamage();

protected:
	virtual void BeginPlay() override;

	virtual void TryMeleeDamage();
};
