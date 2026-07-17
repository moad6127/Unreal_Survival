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

    OnCurrentHealthChanged.AddDynamic(this, &UAttributeComponent::HandleHealthChanged);
}

void UAttributeComponent::Die()
{
    UE_LOG(LogTemp, Warning, TEXT("Character Health Zero!! Die!!"));
}

void UAttributeComponent::HandleHealthChanged(float NewHealth)
{
    
    if (NewHealth <= 0.f)
    {
        Die();
    }
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
