// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Interaction/ExtenedInteractionComponent.h"
#include "InteractionComponent.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;

UCLASS()
class SURVIVAL_API UInteractionComponent : public UExtenedInteractionComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
private:
	void InitInput();

	void StartCanInteractTrace();
	void LineTraceInteraction();
	void HandleInteraction(AActor* HitActor);
	void TargetInteract();

	UFUNCTION()
	void HandleInteractOnDeath();

	UFUNCTION(Server,Reliable)
	void Server_TargetInteract(AActor* ActorToInteract, AController* InstigatingController);

	UFUNCTION()
	void HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InteractContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractInputAction;

	/*
	* LineTrace
	*/
	FTimerHandle TraceTimer;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	float TimerRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace")
	TEnumAsByte<ETraceTypeQuery> InteractTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace")
	float FrontOffsetStartPosition = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction|Trace")
	float TraceLength = 1000.f;

	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
};
