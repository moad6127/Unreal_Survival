// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Respawn/RespawnComponent.h"
#include "Component/Respawn/RespawnHandlerComponent.h"
#include "Component/AttributeManager/AttributeComponent.h"
#include "Utils/SurvivalStatics.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/PlayerStart/RespawnLocation.h"
#include "GameFramework/GameModeBase.h"

void URespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	if (UAttributeComponent* AttributeComp = USurvivalStatics::GetComponentFromActor<UAttributeComponent>(GetOwner()))
	{
		AttributeComp->OnDeath.AddDynamic(this, &URespawnComponent::HandleOnDeath);
	}
}
void URespawnComponent::HandleOnDeath()
{
	Client_InitRespawnUI();
}

void URespawnComponent::Client_InitRespawnUI_Implementation()
{
	APlayerController* PC = USurvivalStatics::GetPlayerControllerFromComponent(this);
	if (!IsValid(PC))
	{
		return;
	}
	if (!RespawnWidgetClass)
	{
		return;
	}

	RespawnWidgetInstance = CreateWidget<UUserWidget>(PC, RespawnWidgetClass);
	if (!IsValid(RespawnWidgetInstance))
	{
		return;
	}

	RespawnWidgetInstance->AddToViewport();

	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);

}

void URespawnComponent::Server_SpawnPlayer_Implementation()
{
	APlayerController* PC = USurvivalStatics::GetPlayerControllerFromComponent(this);
	if (!IsValid(PC))
	{
		return;
	}

	TArray<AActor*> FoundLocations;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARespawnLocation::StaticClass(), FoundLocations);

	ARespawnLocation* RandomLocation = Cast<ARespawnLocation>(FoundLocations[FMath::RandRange(0, FoundLocations.Num() - 1)]);

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (!IsValid(GameMode))
	{
		return;
	}

	if (URespawnHandlerComponent* RespawnHandler = USurvivalStatics::GetComponentFromActor<URespawnHandlerComponent>(GameMode))
	{
		RespawnHandler->SpawnPlayer(PC, RandomLocation);
	}
}
