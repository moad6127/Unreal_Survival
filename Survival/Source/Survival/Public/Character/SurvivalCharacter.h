// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SurvivalCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBasicMovementComponent;
class UFootStepComponent;
class UInputUIComponent;
class UReplicationComponent;
class UInteractionComponent;
class UAttributeComponent;
class URagdollComponent;
class URespawnComponent;
class UInventoryComponent;
class UCraftingComponent;
class UEquipmentComponent;





DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ASurvivalCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBasicMovementComponent> BasicMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFootStepComponent> FootStepComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputUIComponent> UIInputComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UReplicationComponent> ReplicationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URagdollComponent> RagdollComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URespawnComponent> RespawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCraftingComponent> CraftingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

protected:



public:

	/** Constructor */
	ASurvivalCharacter();	

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	UFUNCTION()
	void OnDeath();


};

