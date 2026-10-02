# Unreal_Survival


Unreal Engine 5를 활용해 자원 채집부터 기지 구축까지의 메커니즘을 구현한 멀티플레이어 서바이벌 게임 프로젝트입니다.

외부 하이트맵 기반의 지형 생성 및 자동 머티리얼을 시작으로, 자원 채집(나무 파괴 및 재료 획득), 인벤토리 및 제작(Crafting), 기지 구축을 위한 건축(Building) 시스템 등 서바이벌 장르의 핵심 요소를 구성했습니다.

특히 Udemy의 Build a multiplayer survival framework 강의를 바탕으로 학습을 진행하며, 기존의 블루프린트 로직과 UI 구조를 면밀히 분석한 후 코어 시스템을 C++ 기반으로 재설계 및 모듈화하여 구조적 완성도와 성능을 개선했습니다.



<img width="1938" height="1058" alt="Image" src="https://github.com/user-attachments/assets/ab041926-fd6a-4550-a398-47b7689ec3ac" />

<details><summary> 구분</summary>
<p>  
   
 * [Map](#Map)

 * [Inventory](#Inventory)

 * [Crafting](#Crafting)

 * [BuildingSystem](#BuildingSystem)

 * [Animal AI](#AnimalAI)

</p>
</details>
<br/> <br>   

  ## Map

<img width="1920" height="1008" alt="Image" src="https://github.com/user-attachments/assets/e3cb0faa-1e69-449f-a24e-3bde4f1a4d87" />

> Heightmap 기반 지형 생성: 외부 하이트맵 데이터를 입혀 절차적이고 자연스러운 대형 월드 지형의 기반을 구축했습니다.

> 자동 지형 머티리얼(Auto Landscape Material): 지형의 높이(Height)와 경사도(Slope) 데이터를 기반으로 텍스처가 자동으로 블렌딩되는 머티리얼을 제작해 자연스러운 환경 연출을 구현했습니다.     

  ### World

<img width="1903" height="874" alt="Image" src="https://github.com/user-attachments/assets/195f25ac-99a8-4a7e-a2d2-042ff244fa44" />

> *머티리얼 인스턴스(Material Instance) 기반 모듈화*: 파라미터화된 머티리얼 인스턴스를 활용해 재컴파일 없이 실시간으로 지형 텍스처 및 매핑 기준을 조정할 수 있도록 구성했습니다.

*  높이 및 경사도 연산 매핑:

    * *Height-based Texturing* : 고도에 따라 평지, 풀밭, 바위산 등의 텍스처가 자연스럽게 전환되도록 제어.

    * *Slope-based Texturing* : 절벽이나 급경사 구간에는 바위 텍스처가 자동으로 적용되어 수작업 페인팅 노력을 최소화.


  ### environment

  
  Map에서 자원을 얻기 위해서 나무를 제거하거나 바닥에서 돌을 줍는등의 행동을 할수 있도록 Actor를 폴리지로 생성해서 Map에 넣어 두었다.
  

***Foliage Actors***

  <img width="1938" height="1058" alt="Image" src="https://github.com/user-attachments/assets/3fdd8e4d-77c2-46ea-be36-c1f9dd057c4c" />




```C++
float ABaseTree::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


  ...

	Server_ProcessHit();

	return AppliedDamage;
}

void ABaseTree::Server_ProcessHit_Implementation()
{
  ...

	CurrentOffset = FMath::Min(CurrentOffset + DamageIncrement, MaxOffset);
	ApplyMaskAlpha(); 
  ...
}

void ABaseTree::ApplyMaskAlpha()
{
  ...
	DynamicMaterialInstance->SetScalarParameterValue(OffsetMaskParamName, CurrentOffset);
}

```

 * C++ 기반 ***Procedural Mesh*** 나무 자원 채집 시스템

    * 동적 마스크 연산: 타격 지점에 ***MaterialInstanceDynamic***의 파라미터를 전달하여 실시간으로 나무 상처(Mask Alpha) 효과 연출


```C++

void ABaseTree::Server_ProcessHit_Implementation()
{
  ...

	if (CurrentOffset >= MaxOffset)
	{
		SplitTree();
	}
}

void ABaseTree::SplitTree()
{
  ...
	OnRep_bIsTreeBroken();
}

void ABaseTree::OnRep_bIsTreeBroken()
{

...
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(
		BaseMesh, /*LODIndex=*/0, ProceduralMesh, /*bCreateCollision=*/true);

...


	const FVector PlanePosition = BaseMesh->GetComponentLocation() + FVector(0.f, 0.f, MaskHeight);
	const FVector PlaneNormal(0.25f, 0.25f, 1.f);

	UProceduralMeshComponent* OtherHalf = nullptr;

  //정해진 포지션에서 Slice되도록 만들기
	UKismetProceduralMeshLibrary::SliceProceduralMesh(
		ProceduralMesh,
		PlanePosition,
		PlaneNormal,
		/*bCreateOtherHalf=*/true,
		OtherHalf,
		EProcMeshSliceCapOption::CreateNewSectionForCap,
		CapMaterial);

	TrunkMesh = OtherHalf;
  ...
	
	// 비주얼 정리는 서버/클라 공통으로 같은 타이밍에 실행
	GetWorldTimerManager().SetTimer(
		HideFallenMeshTimerHandle, this, &ABaseTree::HideFallenMesh,
		DurationBeforeSpawningLogsAfterBreak, false);

	// 실제 아이템 스폰은 서버 권위로만
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			SpawnLogsTimerHandle, this, &ABaseTree::SpawnLogs,
			DurationBeforeSpawningLogsAfterBreak, false);
	}
	
}

```

  * 절단 및 메시 분리: ***UKismetProceduralMeshLibrary::SliceProceduralMesh***를 활용해 타격 지점 높이에서 실시간으로 나무 메시 슬라이싱 및 물리(Physics) 적용

  * 이후에 정해진 개수만큼 나무토막을 Spawn하기 위해서 ***SpawnLogs***함수를 호출하기

  ## Inventory

<img width="1938" height="1058" alt="Image" src="https://github.com/user-attachments/assets/aebc44b4-562d-4593-bce7-845bca8f0103" />



  * **슬롯 기반 인벤토리 관리**: Inventory를 담당할 Component의 Beginplay에서 Init을 진행해서 인벤토리를 구성  
	* 인벤토리의 아이템들은 다른 인벤토리 슬롯으로 옮길수도 있도록 만들어져 있음.


```C++

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->HasAuthority())
	{
		InitInventory();
	}
}

void UInventoryComponent::InitInventory()
{
	int32 InitInventoryNum = InventorySlots.Num();
	for (int32 Index = 0; Index < DefaultInventorySlotAmount - InitInventoryNum; Index++)
	{
		CreateEmptySlot(InventorySlots);
	}
}

int32 UInventoryComponent::CreateEmptySlot(TArray<FInventoryItemSlot>& TargetInventory)
{
	FInventoryItemSlot EmptySlot;
	EmptySlot.Item = EmptySlotItem;
	return TargetInventory.Add(EmptySlot);
}

```

```C++
/*Add Item*/
void UInventoryComponent::TryAddItemToInventoryAutomatically(TArray<FInventoryItemSlot>& TargetInventory, const FInventoryItemSlot& ItemToAdd)
{
	int32 EmptyIndex = 0;
	if (FindEmptySlot(TargetInventory, EmptyIndex)) // 인벤토리에 남은 자리를 확인한다.
	{
		AddItemToSlotByIndex(TargetInventory, ItemToAdd, EmptyIndex);
	}
	else // 자리가 없을경우 다시 World에 Spawn하게 만든다.
	{
		SpawnItem(ItemToAdd);
	}
}


/*Drop Item*/

void UInventoryComponent::DropItemBySlotIndex(TArray<FInventoryItemSlot>& TargetInventory, int32 Index)
{
	if (!TargetInventory.IsValidIndex(Index))
	{
		return;
	}
	const FInventoryItemSlot ItemToDrop = TargetInventory[Index]; // 버릴아이템의 인덱스를 찾는다
	SpawnItem(ItemToDrop);

		//버려진 아이템의 인덱스를 다시 초기화 한다.
	SetInventorySlotToEmptyByIndex(TargetInventory, Index); 

}

/*Spawn Item*/
void UInventoryComponent::SpawnItem(const FInventoryItemSlot& ItemToSpawn)
{
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	if (!PickupItemClass || !World || !Owner)
	{
		return;
	}

	FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 10.f;
	SpawnLocation.Z += 50.f;
	const FTransform SpawnTransform(Owner->GetActorRotation(), SpawnLocation, FVector::OneVector);
	APickupItem* SpawnedItem = World->SpawnActorDeferred<APickupItem>(PickupItemClass, SpawnTransform);
	if (SpawnedItem)
	{
		SpawnedItem->SetInventoryItemSlot(ItemToSpawn);
		SpawnedItem->SetSimulatePhysics(true);
		SpawnedItem->FinishSpawning(SpawnTransform);
	}
}

```
  * **자동 아이템 습득 및 월드 드롭**:
    * **Add Item**: 인벤토리 내 빈 슬롯을 찾아 아이템을 추가하며, 남은 공간이 없을 경우 플레이어 앞위치(`SpawnItem`)에 디퍼드 스폰(`World->SpawnActorDeferred`)을 활용해 물리가 적용된 드롭 아이템(`APickupItem`)으로 배치합니다.
    * **Drop Item**: 지정한 슬롯의 아이템을 필드에 스폰하고 해당 슬롯을 비웁니다.

  ### Item

데이터 테이블 기반의 유연한 아이템 구조 설계와 네트워크 리플리케이션을 지원하는 필드 아이템(Pickup) 액터 시스템을 구현했습니다.

### 주요 특징


```cpp
// 데이터 테이블 행 구조체로 아이템 속성(기본 정보, 제작, 능력치)을 묶어 관리
USTRUCT(BlueprintType)
struct FItem : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FItemAttributeGeneric Generic;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FItemAttributeCrafting Crafting;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FItemAssignedAttribute AssignedAttribute;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FDataTableRowHandle CoupledDataTable;
};
```

* **데이터 기반 구조 설계 (`FItem`)**: `FDataTableRowHandle`을 활용해 아이템 메타데이터(`FItemAttributeGeneric`), 제작 레시피(`FItemAttributeCrafting`), 능력치(`FItemAssignedAttribute`)를 데이터 테이블로 일원화 관리하여 확장성을 확보했습니다.


```C++
void APickupItem::Interact_Implementation(AController* InstigatorController)
{
	if (!InstigatorController)
	{
		return;
	}

	if (UInventoryComponent* InventoryComp = USurvivalStatics::GetComponentFromController<UInventoryComponent>(InstigatorController))
	{
		InventoryComp->Server_TryAddItemToInventoryAutomatically(InventoryItemSlot);
	}
	Destroy();
}
```
* **필드 아이템 상호작용 및 습득 처리** : ServerRPC를 활용해서 멀티플레이 환경에서도 획득이 안전하도록 설정

```C++
void APickupItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateFromItemData();
}


void APickupItem::UpdateFromItemData()
{
    FItem ItemData;
    if (!UInventoryStatics::GetInventoryItemInfoFromSlot(InventoryItemSlot, ItemData))
    {
        return;
    }

    // 아이템 정보에 맞춰 필드 메시 및 상호작용 UI 텍스트 동적 설정
    ItemMesh->SetStaticMesh(ItemData.Generic.ItemMesh);
    InteractText = FText::Format(NSLOCTEXT("Pickup", "PickupPrompt", "[E] Pick up {0}"), ItemData.Generic.ItemName);
}
```
* **필드 드롭 및 동적 동기화 (`APickupItem`)**: 필드에 생성되는 아이템은 네트워크 리플리케이션(`ReplicatedUsing`)을 통해 멀티플레이 환경에서 물리(Physics) 및 슬롯 정보(`FInventoryItemSlot`)를 동기화합니다.

* **`OnConstruction` & RepNotify 활용 UI/메시 갱신**: 서버 및 클라이언트에서 아이템 정보가 변경될 때 `UpdateFromItemData()`를 호출해 스태틱 메시 및 상호작용 텍스트(예: `[E] Pick up ...`)를 동적으로 업데이트합니다.

  ### Equipmemt

```C++
  void UEquipmentComponent::Equip(const FInventoryItemSlot& ItemToEquip,int32 Index)
{
	...
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

void UEquipmentComponent::SpawnAndAttach(const FEquipmentItem& EquipmentInfoToSpawn)
{
	...
	const FTransform SpawnTransform = FTransform::Identity;
	AEquipActor* NewEquipActor = World->SpawnActorDeferred<AEquipActor>(EquipActorClass, SpawnTransform, GetOwner(), Cast<APawn>(GetOwner()));
	if (!NewEquipActor)
	{
		return;
	}
	NewEquipActor->EquipmentInfo = EquipmentInfoToSpawn;
	NewEquipActor->FinishSpawning(SpawnTransform);
	NewEquipActor->SetOwner(GetOwner());

	if (USkeletalMeshComponent* OwnerMesh = GetOwnerMesh())
	{
		NewEquipActor->AttachToComponent(OwnerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquipmentInfoToSpawn.Equip.SocketName);
		NewEquipActor->SetActorRelativeTransform(EquipmentInfoToSpawn.Equip.SocketOffset.ToTransform());
	}

	EquippedWeaponActor = NewEquipActor;
}
```

* 액터 스폰 및 소켓 부착 : 아이템 장착 시 `FEquipmentItem` 데이터 테이블 정보를 조회해 지정된 `AEquipActor` 클래스를 디퍼드 스폰(SpawnActorDeferred) 후, 캐릭터 스켈레탈 메시의 지정 소켓(SocketName) 및 오프셋에 자동 부착합니다.

```C++
/*장착된 아이템을 해제할때 호출되는 함수.*/
void UEquipmentComponent::UnequipToSlot(int32 DestinationIndex)
{
	...
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

/*캐릭터가 죽었을경우 호출되는 함수*/
void UEquipmentComponent::HandleOnDeath()
{
	DetachEquipment();
}

void UEquipmentComponent::DetachEquipment()
{
	if (EquippedWeaponActor)
	{
		EquippedWeaponActor->SetOwner(nullptr);
		EquippedWeaponActor->Destroy();
		EquippedWeaponActor = nullptr;
	}
}


```
* 장착을 해제 및 사망 처리 : 장착을 해제하거나 캐릭터가 사망처리 되었을때는 장착된 아이템을 해제하도록 만든다.


## Crafting

<img width="1938" height="1058" alt="Image" src="https://github.com/user-attachments/assets/515401e7-1bf3-4ce3-91ac-b27fd6f1005a" />


데이터 테이블 기반의 유연한 제작 레시피 관리와 FTimerManager 기반의 비동기 제작 타이머, 그리고 네트워크 리플리케이션을 지원하는 제작(Crafting) 시스템을 구현했습니다.

### 주요 특징

```C++
void UCraftingComponent::SetDefaultRecipesFromDataTable()
{
	if (!ItemDataTable)
	{
		return;
	}
	for (const FName& RowName : ItemDataTable->GetRowNames())
	{
		const FItem* Row = ItemDataTable->FindRow<FItem>(RowName, TEXT("SetDefaultRecipesFromDataTable"));
		if (!Row || !Row->Crafting.bIsCraftable)
		{
			continue;
		}

		//중복일경우 넘기기
		const bool bAlreadyKnown = Recipes.ContainsByPredicate([&RowName, this](const FInventoryItemSlot& Existing)
			{
				return Existing.Item.DataTable == ItemDataTable && Existing.Item.RowName == RowName;
			});

		if (bAlreadyKnown)
		{
			continue;
		}

		FInventoryItemSlot NewRecipeSlot;
		NewRecipeSlot.Item.DataTable = ItemDataTable;
		NewRecipeSlot.Item.RowName = RowName;
		NewRecipeSlot.Amount = 1;

		Recipes.Add(NewRecipeSlot);
	}
}
```
- **데이터 기반 레시피 자동 로드 (`SetDefaultRecipesFromDataTable`)**
  - `UDataTable`을 순회하여 `bIsCraftable` 속성이 활성화된 아이템 동적 파싱 및 레시피 자동 등록
  - 기존에 알려진 레시피 중복 등록 방지 로직 적용

```C++
void UCraftingComponent::TryCraftItem(const FInventoryItemSlot& ItemToCraft)
{
	//이미 크래프팅중이라면 넘기기,
	if (bIsCrafting)
	{
		return;
	}
	...

	// 인벤토리에 제작에 필요한 아이템들이 존재하는지 확인하기
	if (!InventoryComponent->CanArrayOfItemsBeFoundInInventory(ItemRow->Crafting.Recipe))
	{
		UE_LOG(LogTemp, Log, TEXT("Not sufficient items to craft %s"), *ItemToCraft.Item.RowName.ToString());
		return;
	}

	// 제작에 사용된 아이템들은 제거
	for (const FInventoryItemSlot& RecipeIngredient : ItemRow->Crafting.Recipe)
	{
		InventoryComponent->Server_RemoveItemFromInventoryAutomatically(RecipeIngredient, RecipeIngredient.Amount);
	}

	StartCrafting(ItemToCraft);
}

void UCraftingComponent::StartCrafting(const FInventoryItemSlot& ItemToStartCrafting)
{
	bIsCrafting = true;
	CurrentlyCraftingItem = ItemToStartCrafting;

	StartingCraftingTime = DefaultCraftingTime;
	CurrentCraftingTime = StartingCraftingTime;

	// Timer를 계속생성하지 않고 한번만 생성한후 Pause를 사용해서 재사용하도록 만들기
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (CraftingTimerHandle.IsValid())
	{
		TimerManager.UnPauseTimer(CraftingTimerHandle);
	}
	else
	{
		TimerManager.SetTimer(CraftingTimerHandle, this, &UCraftingComponent::TickCraftingTimer, CraftingTickInterval, true);
	}
}

void UCraftingComponent::TickCraftingTimer()
{
	CurrentCraftingTime -= CraftingTickInterval;

	if (CurrentCraftingTime > 0.f)
	{
		return;
	}

	GetWorld()->GetTimerManager().PauseTimer(CraftingTimerHandle);

	if (UExtenedInventoryComponent* InventoryComponent = USurvivalStatics::GetComponentFromActor<UExtenedInventoryComponent>(GetOwner()))
	{
		InventoryComponent->Server_TryAddItemToInventoryAutomatically(CurrentlyCraftingItem);
	}

	CurrentlyCraftingItem = FInventoryItemSlot();
	bIsCrafting = false;
}

```
- **`FTimerManager` 기반 비동기 진행 (`StartCrafting`, `TickCraftingTimer`)**
  - 매 프레임 Tick 대신 지정된 타이머 간격(`CraftingTickInterval`)으로 잔여 제작 시간을 감소시켜 성능 최적화
  - 제작 완료 시 서버 권위로 인벤토리에 결과 아이템을 자동 추가(`Server_TryAddItemToInventoryAutomatically`)


---



## BuildingSystem


## AnimalAI
  
