// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedInteractionComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedInteractionComponent();

protected:
	virtual void BeginPlay() override;
	
};
