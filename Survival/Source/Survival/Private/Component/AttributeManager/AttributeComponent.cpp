// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeManager/AttributeComponent.h"

void UAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    InitValues();
}

void UAttributeComponent::InitValues()
{
    OnMaxHealthChanged.Broadcast(MaxHealth);
    OnMaxFoodChanged.Broadcast(MaxFood);
    OnMaxHydrationChanged.Broadcast(MaxHydration);
    OnCurrentHealthChanged.Broadcast(CurrentHealth);
    OnCurrentFoodChanged.Broadcast(CurrentFood);
    OnCurrentHydrationChanged.Broadcast(CurrentHydration);
}

void UAttributeComponent::ModifyAttribute(EAttributeTypes AttributeType, float Amount)
{
    switch (AttributeType)
    {
    case EAttributeTypes::Health:
        SetCurrentHealth(GetCurrentHealth() + Amount);
        break;
    case EAttributeTypes::Food:
        SetCurrentFood(GetCurrentFood() + Amount);
        break;
    case EAttributeTypes::Hydration:
        SetCurrentHydration(GetCurrentHydration() + Amount);
        break;
    default:
        break;
    }
}
