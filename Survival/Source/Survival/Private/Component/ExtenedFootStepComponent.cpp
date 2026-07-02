// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ExtenedFootStepComponent.h"


UExtenedFootStepComponent::UExtenedFootStepComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UExtenedFootStepComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UExtenedFootStepComponent::Execute_FootStep_Logic(USkeletalMeshComponent* MeshComp, bool IsRightFoot)
{
}


