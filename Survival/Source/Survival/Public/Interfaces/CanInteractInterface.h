// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanInteractInterface.generated.h"

// This class does not need to be modified.

class AController;
class USoundBase;
class UAnimMontage;

UINTERFACE(MinimalAPI)
class UCanInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVAL_API ICanInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool CanInteract(AController* InstigatorController);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractText(AController* InstigatorController);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FVector GetInteractTextLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool ShouldExecuteInteractionOnServer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ShowInteractPrompt();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void HideInteractPrompt();

	/*
	* Optional
	*/
	/*
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	USoundBase* GetInteractionSound();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	UAnimMontage* GetInteractionAnimation();
	*/

};
