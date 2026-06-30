// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputMappingContext.h"
#include "SurvivalStatics.generated.h"

/**
 * 
 */
class UEnhancedInputLocalPlayerSubsystem;
class ACharacter;
class AController;
class APlayerController;

UCLASS()
class SURVIVAL_API USurvivalStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

    /* 입력 함수들*/

    /**
     * Mapping Context를 추가합니다.
     *
     * @param PlayerController   대상 플레이어 컨트롤러
     * @param MappingContext     등록할 Input Mapping Context
     * @param Priority           우선순위 (높을수록 먼저 처리됨, 기본값 0)
     */
    UFUNCTION(BlueprintCallable, Category = "Statics|Input")
    static void LinkInputMappingContext(APlayerController* PlayerController,UInputMappingContext* MappingContext,int32 Priority = 0);

    /**
     * Mapping Context를 제거합니다.
     *
     * @param PlayerController   대상 플레이어 컨트롤러
     * @param MappingContext     제거할 Input Mapping Context
     */
    UFUNCTION(BlueprintCallable, Category = "Statics|Input")
    static void UnlinkInputMappingContext(APlayerController* PlayerController,UInputMappingContext* MappingContext);

    /**
     * 기존 Mapping Context를 제거하고 새 Context로 교체합니다.
     *
     * @param PlayerController   대상 플레이어 컨트롤러
     * @param OldMappingContext  제거할 기존 Context
     * @param NewMappingContext  추가할 새 Context
     * @param Priority           새 Context의 우선순위
     */
    UFUNCTION(BlueprintCallable, Category = "Statics|Input")
    static void SwitchInputMappingContext(APlayerController* PlayerController,UInputMappingContext* OldMappingContext,UInputMappingContext* NewMappingContext,int32 Priority = 0);

    /*Component 헬퍼*/

    /*
    */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Statics|Component")
    static ACharacter* GetCharacterFromComponent(const UActorComponent* Component);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Statics|Component")
    static AController* GetControllerFromComponent(const UActorComponent* Component);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Statics|Component")
    static APlayerController* GetPlayerControllerFromComponent(const UActorComponent* Component);
private:

    /**
    * PlayerController에서 Enhanced Input Subsystem을 가져오는 내부 헬퍼.
    *
    * @param PlayerController  대상 플레이어 컨트롤러
    * @return Enhanced Input Local Player Subsystem (없으면 nullptr)
    */
    static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem(APlayerController* PlayerController);

};
