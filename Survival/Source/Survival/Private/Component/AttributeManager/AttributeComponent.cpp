// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeManager/AttributeComponent.h"
#include "Kismet/GameplayStatics.h"

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



void UAttributeComponent::ApplyStatDamage()
{
    if (GetCurrentFood() <= 0.f)
    {
        UGameplayStatics::ApplyDamage(GetOwner(), FoodZeroDamage, nullptr, nullptr, nullptr);
    }
    if (GetCurrentHydration() <= 0.f)
    {
        UGameplayStatics::ApplyDamage(GetOwner(), HydrationZeroDamage, nullptr, nullptr, nullptr);
    }
}

