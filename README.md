# Unreal_Survival

```
Unreal Engine 5를 활용해 자원 채집부터 기지 구축까지의 메커니즘을 구현한 멀티플레이어 서바이벌 게임 프로젝트입니다.

외부 하이트맵 기반의 지형 생성 및 자동 머티리얼을 시작으로, 자원 채집(나무 파괴 및 재료 획득), 인벤토리 및 제작(Crafting), 기지 구축을 위한 건축(Building) 시스템 등 서바이벌 장르의 핵심 요소를 구성했습니다.

특히 Udemy의 Build a multiplayer survival framework 강의를 바탕으로 학습을 진행하며, 기존의 블루프린트 로직과 UI 구조를 면밀히 분석한 후 코어 시스템을 C++ 기반으로 재설계 및 모듈화하여 구조적 완성도와 성능을 개선했습니다.
```


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

  ```
  Map에서 자원을 얻기 위해서 나무를 제거하거나 바닥에서 돌을 줍는등의 행동을 할수 있도록 Actor를 폴리지로 생성해서 Map에 넣어 두었다.
  ```

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
  
  ### Item
  ### Equipmemt

  ## Crafting

  ## BuildingSystem

  ## AnimalAI
  
