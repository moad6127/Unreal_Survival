// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedRagdollComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedRagdollComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedRagdollComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Ragdoll")
	void Server_Ragdoll(bool NewRagdolling);
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnRep_bRagdolling();

	virtual void ToRagdoll();

	UPROPERTY(ReplicatedUsing = OnRep_bRagdolling, BlueprintReadOnly, Category = "Ragdolling")
	bool bRagdolling = false;
};
