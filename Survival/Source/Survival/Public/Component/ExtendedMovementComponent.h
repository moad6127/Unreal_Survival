// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtendedMovementComponent.generated.h"


UCLASS(Abstract,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API UExtendedMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExtendedMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool DisableMovement = false;
public:	

		
};
