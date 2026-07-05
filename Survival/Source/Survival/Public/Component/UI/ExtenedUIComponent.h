// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedUIComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedUIComponent();

protected:
	virtual void BeginPlay() override;

public:	

		
};
