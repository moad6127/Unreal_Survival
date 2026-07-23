// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API UExtenedInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedInventoryComponent();

protected:
	virtual void BeginPlay() override;

	
};
