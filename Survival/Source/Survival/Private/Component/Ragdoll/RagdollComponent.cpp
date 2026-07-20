// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Ragdoll/RagdollComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Utils/SurvivalStatics.h"
#include "Component/AttributeManager/ExtendedAttributeComponent.h"

void URagdollComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UExtendedAttributeComponent* AttributeComponent = USurvivalStatics::GetComponentFromActor<UExtendedAttributeComponent>(GetOwner()))
	{
		AttributeComponent->OnDeath.AddDynamic(this, &URagdollComponent::HandleOnDeath);
	}
}

void URagdollComponent::OnRep_bRagdolling()
{
	Super::OnRep_bRagdolling();
}

void URagdollComponent::ToRagdoll()
{
	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
	if (!OwningCharacter)
	{
		return;
	}
	USkeletalMeshComponent* Mesh = OwningCharacter->GetMesh();
	if (!Mesh)
	{
		return;
	}

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetAllBodiesBelowSimulatePhysics(RagdollBoneName, true, true);
	Mesh->bUpdateJointsFromAnimation = true;

	OwningCharacter->GetCharacterMovement()->DisableMovement();
	OwningCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void URagdollComponent::HandleOnDeath()
{
	Server_Ragdoll(true);
}

