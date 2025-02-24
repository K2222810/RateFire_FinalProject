// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "SimplehooterGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "PlayerAnimationInstance.h"
#include "StatsComponent.h"
#include "EStat.h"
#include "AimComponent.h"
#include "LockOn.h"
#include "CombaComponent.h"
#include "TraceComponent.h"
#include "BlockComponent.h"
#include "PlayerActionsComponent.h"

// Sets default values
AShooter::AShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimComp = CreateDefaultSubobject<UAimComponent>(TEXT("Aim Component"));
	LockonComp = CreateDefaultSubobject<ULockOn>(TEXT("Lockon Component"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace Component"));
	CombatComp = CreateDefaultSubobject<UCombaComponent>(TEXT("Combat Component"));

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	BlockComp = CreateDefaultSubobject<UBlockComponent>(TEXT("Block Component"));
	PlayerActionsComp = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("Player Actions Component"));


}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{

	Super::BeginPlay();
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	ActiveIndex = 0;
	UE_LOG(LogTemp, Warning, TEXT("ActiveIndex = %d"), ActiveIndex);

	for (int32 Index = 0; Index < 3; Index++)
	{
		CurrentGun[Index] = GetWorld()->SpawnActor<AGun>(GunClass[Index]);

		if (CurrentGun[Index])
		{
			CurrentGun[Index]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			CurrentGun[Index]->SetOwner(this);
			UE_LOG(LogTemp, Warning, TEXT("Attached mesh number %d"), Index);

			if (Index != ActiveIndex)
			{
				CurrentGun[Index]->SetActorHiddenInGame(true);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No gun attached on %d"), Index);
		}
	}

}

bool AShooter::IsDead() const
{
	if (StatsComp->Stats[EStat::Health] <= 0)
	{
		return true;
	}
	return false;
}


// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooter::Shoot);
	PlayerInputComponent->BindAxis(TEXT("SwitchingWeapons"), this, &AShooter::SwapUp);
}

float AShooter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(StatsComp->Stats[EStat::Health], DamageToApply);
	if (IsDead())
	{

		ASimplehooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASimplehooterGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return DamageToApply;
}

void AShooter::MoveForward(float AxisValue)
{

	AddMovementInput(GetActorForwardVector() * AxisValue);

}

void AShooter::MoveRight(float AxisValue)
{

	AddMovementInput(GetActorRightVector() * AxisValue);

}


void AShooter::LookUpRate(float AxisValue)
{

	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooter::Shoot()
{
	CurrentGun[ActiveIndex]->PullTrigger();
}

void AShooter::SwapUp(float Slot)
{
	int32 SlotIndex = static_cast<int32>(Slot);
	CurrentGun[ActiveIndex]->SetActorHiddenInGame(true);
	ActiveIndex += SlotIndex;
	ActiveIndex = FMath::Clamp(ActiveIndex, 0, 2);
	CurrentGun[ActiveIndex]->SetActorHiddenInGame(false);

}

float  AShooter::GetHealthPercent() const
{
	return StatsComp->Stats[EStat::Health] / StatsComp->Stats[EStat::MaxHealth];
}

float  AShooter::GetStaminaPercent() const
{
	return StatsComp->Stats[EStat::Stamina] / StatsComp->Stats[EStat::MaxStamina];
}

void AShooter::PlayHurtAnim()
{

	PlayAnimMontage(HurtAnimMontage);
}

// Called every frame
float AShooter::GetDamage()
{

	return StatsComp->Stats[EStat::Strength];

}

bool AShooter::HasEnoughStamina(float Cost)
{
	return StatsComp->Stats[EStat::Stamina] >= Cost;
}

