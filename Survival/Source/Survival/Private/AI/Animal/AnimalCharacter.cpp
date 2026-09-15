// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animal/AnimalCharacter.h"
#include "Net/UnrealNetwork.h"
#include "MotionWarpingComponent.h"
#include "Component/AttributeManager/AttributeComponent.h"
#include "Component/Replication/ReplicationComponent.h"
#include "Component/Ragdoll/RagdollComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Animal/AnimalAIController.h"

AAnimalCharacter::AAnimalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	ReplicationComponent = CreateDefaultSubobject<UReplicationComponent>(TEXT("ReplicationComponent"));
	RagdollComponent = CreateDefaultSubobject<URagdollComponent>(TEXT("RagdollComponent"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	bUseControllerRotationYaw = false;
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->bOrientRotationToMovement = false;
	}
}

void AAnimalCharacter::SetIdleAction(EAnimalIdleAction NewAction)
{
	if (!HasAuthority())
	{
		return;
	}

	CurrentIdleAction = NewAction;
}

void AAnimalCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAnimalCharacter, CurrentIdleAction);
}

void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		return;
	}


	if (AttributeComponent)
	{
		AttributeComponent->OnDeath.AddDynamic(this, &AAnimalCharacter::HandleDeath);
	}

	OnTakeAnyDamage.AddDynamic(this, &AAnimalCharacter::HandleAnyDamage);
}

void AAnimalCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector Velocity = GetVelocity();
	if (Velocity.SizeSquared2D() < 1.f)
	{
		return;  // ¸ØÃçÀÖÀ¸¸é È¸Àü ¾È ÇÔ
	}

	const FRotator CurrentRotation = GetActorRotation();
	const FRotator TargetRotation = Velocity.GetSafeNormal2D().Rotation();

	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, TurnInterpSpeed);
	SetActorRotation(FRotator(0.f, NewRotation.Yaw, 0.f));
}


void AAnimalCharacter::HandleDeath()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBrainComponent* Brain = AIController->GetBrainComponent())
		{
			Brain->StopLogic(TEXT("Died"));
		}
	}

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, [this]() { Destroy(); }, 5.f, false);
}

void AAnimalCharacter::HandleAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!HasAuthority())
	{
		return;
	}

	AAnimalAIController* AIController = Cast<AAnimalAIController>(GetController());
	if (!AIController)
	{
		return;
	}

	if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
	{
		BlackboardComp->SetValueAsBool(TEXT("WasAttacked"), true);
	}

	if (InstigatedBy)
	{
		AIController->NotifyThreatDetected(InstigatedBy->GetPawn());
	}
}

void AAnimalCharacter::FaceTarget(AActor* Target)
{
	if (!Target)
	{
		return;
	}

	const FVector ToTarget = Target->GetActorLocation() - GetActorLocation();
	const FRotator LookAtRotation = ToTarget.Rotation();

	SetActorRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));
}

void AAnimalCharacter::SetAlertMovementSpeed()
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = AlertWalkSpeed;
	}
}
