// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/ExtenedUIComponent.h"
#include "InputUIComponent.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class UUserWidget;

UCLASS()
class SURVIVAL_API UInputUIComponent : public UExtenedUIComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

private:
	void OpenAndCloseInGameMenuClicked();
	void CreateInGameMenu();
	void OpenInGameMenu();
	void CloseInGameMenu();

	UFUNCTION()
	void HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

	UFUNCTION()
	void HandleUIOnDeath();

	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> UIMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenAndCloseInGameMenu;

	bool InGameMenuActive = false;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> InGameMenuWidget;

};
