// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeManager/ExtendedAttributeComponent.h"

UExtendedAttributeComponent::UExtendedAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UExtendedAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}



void UExtendedAttributeComponent::SetMaxHealth(float InHealth)
{
    MaxHealth = InHealth;
    OnMaxHealthChanged.Broadcast(MaxHealth);
}

void UExtendedAttributeComponent::SetMaxFood(float InFood)
{
    MaxFood = InFood;
    OnMaxFoodChanged.Broadcast(MaxFood);
}

void UExtendedAttributeComponent::SetMaxHydration(float InHydration)
{
    MaxHydration = InHydration;
    OnMaxHydrationChanged.Broadcast(MaxHydration);
}

void UExtendedAttributeComponent::SetCurrentHealth(float InHealth)
{
    const float ClampedValue = FMath::Clamp(InHealth, 0.f, MaxHealth);
    if (FMath::IsNearlyEqual(ClampedValue, CurrentHealth))
    {
        return; // 값이 실제로 안 바뀌었으면 브로드캐스트하지 않음
    }

    CurrentHealth = ClampedValue;
    OnCurrentHealthChanged.Broadcast(CurrentHealth);
}

void UExtendedAttributeComponent::SetCurrentFood(float InFood)
{
    const float ClampedValue = FMath::Clamp(InFood, 0.f, MaxFood);
    if (FMath::IsNearlyEqual(ClampedValue, CurrentFood))
    {
        return; // 값이 실제로 안 바뀌었으면 브로드캐스트하지 않음
    }

    CurrentFood = ClampedValue;
    OnCurrentFoodChanged.Broadcast(CurrentFood);
}

void UExtendedAttributeComponent::SetCurrentHydration(float InHydration)
{
    const float ClampedValue = FMath::Clamp(InHydration, 0.f, MaxHydration);
    if (FMath::IsNearlyEqual(ClampedValue, CurrentHydration))
    {
        return; // 값이 실제로 안 바뀌었으면 브로드캐스트하지 않음
    }

    CurrentHydration = ClampedValue;
    OnCurrentHydrationChanged.Broadcast(CurrentHydration);
}


