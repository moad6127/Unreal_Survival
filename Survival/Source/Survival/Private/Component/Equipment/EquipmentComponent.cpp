// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Equipment/EquipmentComponent.h"
#include "Component/Inventory/ExtenedInventoryComponent.h"
#include "Utils/EquipmentStatics.h"
#include "Utils/SurvivalStatics.h"
#include "Utils/InventoryStatics.h"
#include "Types/EquipmentTypes.h"
#include "Actors/EquipActor/EquipActor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		OwnerPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UEquipmentComponent::HandleControllerChanged);
		if (AController* CurrentController = OwnerPawn->GetController())
		{
			HandleControllerChanged(OwnerPawn, nullptr, CurrentController);
		}
	}
}
void UEquipmentComponent::HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	APlayerController* OwnerPlayerController = Cast<APlayerController>(NewController);
	if (!IsValid(OwnerPlayerController))
	{
		return;
	}
	USurvivalStatics::LinkInputMappingContext(OwnerPlayerController, EquipmentContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerPlayerController->InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}

	if (EquipmentInputAction)
	{
		EnhancedInputComponent->BindAction(EquipmentInputAction, ETriggerEvent::Completed, this, &UEquipmentComponent::Server_TryExecutePrimaryEquipmentAction);
	}
}


void UEquipmentComponent::Equip(const FInventoryItemSlot& ItemToEquip,int32 Index)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	// 이미 뭔가 장착되어 있으면 아무 것도 하지 않는다 (스왑은 나중에 확장 가능)
	if (!UInventoryStatics::IsItemEmpty(EquipmentItem, EmptyItem))
	{
		return;
	}

	// 이 아이템이 장착 가능한지 확인 (FItem.CoupledDataTable을 통해 DT_Equipment 조회). 못 찾으면 아무 것도 하지 않는다.
	FEquipmentItem EquipmentInfo;
	if (!UEquipmentStatics::GetEquipmentInfoFromInventorySlot(ItemToEquip, EquipmentInfo))
	{
		return;
	}
	UExtenedInventoryComponent* InventoryComp = USurvivalStatics::GetComponentFromComponent<UExtenedInventoryComponent>(this);
	if (!InventoryComp)
	{
		return;
	}
	InventoryComp->RemoveItemAtSlotIndex(Index);
	
	SetEquipmentSlot(ItemToEquip);
	SpawnAndAttach(EquipmentInfo);
	// 서버는 자기 자신의 OnRep_EquipmentItem을 받지 못하므로 직접 브로드캐스트
	OnEquipmentSlotUpdated.Broadcast(EquipmentItem);
}

void UEquipmentComponent::Unequip()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	// 장착된 게 없으면 아무 것도 하지 않는다
	
	if (UInventoryStatics::IsItemEmpty(EquipmentItem, EmptyItem))
	{
		return;
	}
	UExtenedInventoryComponent* InventoryComp = USurvivalStatics::GetComponentFromComponent<UExtenedInventoryComponent>(this);
	if (!InventoryComp)
	{
		return;
	}

	InventoryComp->Server_TryAddItemToInventoryAutomatically(EquipmentItem);

	FInventoryItemSlot EmptySlot;
	EmptySlot.Item = EmptyItem;
	EmptySlot.Amount = 1;
	SetEquipmentSlot(EmptySlot);

	DetachEquipment();

	OnEquipmentSlotUpdated.Broadcast(EquipmentItem);
}

void UEquipmentComponent::UnequipToSlot(int32 DestinationIndex)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if (UInventoryStatics::IsItemEmpty(EquipmentItem, EmptyItem))
	{
		return;
	}

	UExtenedInventoryComponent* InventoryComp = USurvivalStatics::GetComponentFromComponent<UExtenedInventoryComponent>(this);
	if (!InventoryComp)
	{
		return;
	}

	if (!InventoryComp->AddItemAtSlotIndex(EquipmentItem, DestinationIndex))
	{
		return;
	}

	FInventoryItemSlot EmptySlot;
	EmptySlot.Item = EmptyItem;
	EmptySlot.Amount = 1;
	SetEquipmentSlot(EmptySlot);

	DetachEquipment();

	OnEquipmentSlotUpdated.Broadcast(EquipmentItem);
}

void UEquipmentComponent::TryExecutePrimaryEquipmentAction()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}
	if (EquippedWeaponActor)
	{
		EquippedWeaponActor->TryPrimaryAction();
	}
}

void UEquipmentComponent::SetEquipmentSlot(const FInventoryItemSlot& ItemToEquip)
{
	EquipmentItem = ItemToEquip;
}

void UEquipmentComponent::SpawnAndAttach(const FEquipmentItem& EquipmentInfoToSpawn)
{
	if (!EquipActorClass || !GetOwner())
	{
		return;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const FTransform SpawnTransform = FTransform::Identity;
	AEquipActor* NewEquipActor = World->SpawnActorDeferred<AEquipActor>(EquipActorClass, SpawnTransform, GetOwner(), Cast<APawn>(GetOwner()));
	if (!NewEquipActor)
	{
		return;
	}
	NewEquipActor->EquipmentInfo = EquipmentInfoToSpawn;
	NewEquipActor->FinishSpawning(SpawnTransform);

	if (USkeletalMeshComponent* OwnerMesh = GetOwnerMesh())
	{
		NewEquipActor->AttachToComponent(OwnerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquipmentInfoToSpawn.Equip.SocketName);
		NewEquipActor->SetActorRelativeTransform(EquipmentInfoToSpawn.Equip.SocketOffset.ToTransform());
	}

	EquippedWeaponActor = NewEquipActor;
}

void UEquipmentComponent::DetachEquipment()
{
	if (EquippedWeaponActor)
	{
		EquippedWeaponActor->Destroy();
		EquippedWeaponActor = nullptr;
	}
}
