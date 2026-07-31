// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeManager/AttributeComponent.h"
#include "Component/Inventory/ExtenedInventoryComponent.h"
#include "Utils/InventoryStatics.h"
#include "Utils/SurvivalStatics.h"
#include "Kismet/GameplayStatics.h"


void UAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    InitValues();

    if (GetOwner()->HasAuthority())
    {
        StartStatConsumeTimer();

        if (UExtenedInventoryComponent* InventoryComp = USurvivalStatics::GetComponentFromActor<UExtenedInventoryComponent>(GetOwner()))
        {
            InventoryComp->OnItemConsumed.AddDynamic(this, &UAttributeComponent::HandleItemConsume);
        }
    }
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

void UAttributeComponent::StartStatConsumeTimer()
{
    GetWorld()->GetTimerManager().SetTimer(
        StatConsumeTimer,
        this,
        &UAttributeComponent::HandleStatConsumeTick,
        StatConsumeRate,
        true);
}

void UAttributeComponent::HandleStatConsumeTick()
{
    ModifyAttribute(EAttributeTypes::Food, -FoodConsumeDamage);
    ModifyAttribute(EAttributeTypes::Hydration, -HydrationConsumeDamage);

    ApplyStatDamage();
}

void UAttributeComponent::HandleItemConsume(FInventoryItemSlot ConsumedItem)
{
    FItem ItemInfo;
    if (!UInventoryStatics::GetInventoryItemInfoFromSlot(ConsumedItem, ItemInfo))
    {
        return;
    }
    ModifyAttribute(ItemInfo.AssignedAttribute.AttributeType, ItemInfo.AssignedAttribute.Amount);
}

