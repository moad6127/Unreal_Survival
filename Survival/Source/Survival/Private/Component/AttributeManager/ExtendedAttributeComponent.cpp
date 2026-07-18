// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeManager/ExtendedAttributeComponent.h"
#include "Net/UnrealNetwork.h"

UExtendedAttributeComponent::UExtendedAttributeComponent()
{
    SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UExtendedAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UExtendedAttributeComponent, CurrentHealth);
    DOREPLIFETIME(UExtendedAttributeComponent, CurrentFood);
    DOREPLIFETIME(UExtendedAttributeComponent, CurrentHydration);
}


void UExtendedAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
    if(AActor* Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UExtendedAttributeComponent::HandleTakeAnyDamage);
    }
}

void UExtendedAttributeComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Server_ApplyDamage(Damage, DamageType, InstigatedBy, DamageCauser);
}

void UExtendedAttributeComponent::Server_ApplyDamage_Implementation(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (GetCurrentHealth() <= 0.f || Damage <= 0.f)
    {
        return;
    }

    ModifyAttribute(EAttributeTypes::Health, -Damage);

    if (!bIsDead && CurrentHealth <= 0.f)
    {
        bIsDead = true;
        OnDeath.Broadcast();
    }
}

void UExtendedAttributeComponent::ModifyAttribute(EAttributeTypes AttributeType, float Amount)
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

void UExtendedAttributeComponent::OnRep_CurrentHealth()
{
    OnCurrentHealthChanged.Broadcast(CurrentHealth);

    if (!bIsDead && CurrentHealth <= 0.f)
    {
        bIsDead = true;
        OnDeath.Broadcast();
    }
}

void UExtendedAttributeComponent::OnRep_CurrentFood()
{
    OnCurrentFoodChanged.Broadcast(CurrentFood);
}

void UExtendedAttributeComponent::OnRep_CurrentHydration()
{
    OnCurrentHydrationChanged.Broadcast(CurrentHydration);
}


