// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CanInteractInterface.h"
#include "Interfaces/InteractInterface.h"
#include "BaseInteractActor.generated.h"

class USphereComponent;
class UWidgetComponent;

UCLASS()
class SURVIVAL_API ABaseInteractActor : public AActor, public ICanInteractInterface, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ABaseInteractActor();

public:

	/*
	*IInteractInterface
	*/
	virtual void Interact_Implementation(AController* InstigatorController) override;
	/*
	*IInteractInterface
	*/

	/*
	* ICanInteractInterface
	*/
	virtual bool CanInteract_Implementation(AController* InstigatorController) override;
	virtual FText GetInteractText_Implementation(AController* InstigatorController) override;
	virtual FVector GetInteractTextLocation_Implementation() override;
	virtual bool ShouldExecuteInteractionOnServer_Implementation() override;
	virtual void ShowInteractPrompt_Implementation() override;
	virtual void HideInteractPrompt_Implementation() override;
	/*
	* ICanInteractInterface
	*/
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> InteractWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FVector InteractTextLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bExecuteInteractionOnServer;
};
