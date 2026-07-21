// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Survival_GameMode.h"
#include "Component/Respawn/RespawnHandlerComponent.h"

ASurvival_GameMode::ASurvival_GameMode()
{
	RespawnHandlerComponent = CreateDefaultSubobject<URespawnHandlerComponent>(TEXT("RespawnHandler"));

}
