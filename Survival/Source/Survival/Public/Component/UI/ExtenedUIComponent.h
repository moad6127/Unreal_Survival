// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtenedUIComponent.generated.h"


UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UExtenedUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExtenedUIComponent();

	UFUNCTION(BlueprintPure, Category = "UI")
	bool IsInGameMenuActive() const { return bInGameMenuActive; }

	// 항상 오너 클라이언트에서 실행 ? 빌드 모드 시작 등 다른 시스템에서 UI를 강제로 닫을 때 사용
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UI")
	virtual void CloseUI();

protected:
	virtual void BeginPlay() override;

	bool bInGameMenuActive = false;
public:	

		
};
