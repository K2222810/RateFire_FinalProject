// Fill out your copyright notice in the Description page of Project Settings.


#include "Juggernat.h"
#include "StatsComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CombaComponent.h"
#include "TraceComponent.h"
#include "Shooter.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"



// Sets default values
AJuggernat::AJuggernat()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace Component"));
	CombatComp = CreateDefaultSubobject<UCombaComponent>(TEXT("Combat Component"));

}

// Called when the game starts or when spawned
void AJuggernat::BeginPlay()
{	
	Super::BeginPlay();


	// Get the AI Controller
	ControllerRef = GetController<AAIController>();
	if (!ControllerRef)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller is null!"));
		return; // Exit if the controller is invalid
	}

	// Get the Blackboard Component
	BlackboardComp = ControllerRef->GetBlackboardComponent();
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Blackboard Component is null!"));
		return; // Exit if the blackboard is invalid
	}

	// Set the initial state in the Blackboard
	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState
	);
}

// Called every frame
void AJuggernat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJuggernat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AJuggernat::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{	
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(StatsComp->Stats[EStat::Health], DamageToApply);
	if (IsDead())
	{	

		HandleDeath();
	}
	return DamageToApply;
}


void AJuggernat::DetectPawn(APawn* PawnDetected, APawn* PawnCheck)
{
	EEnemyState CurrentState{
		static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
	};

	if (PawnDetected != PawnCheck || CurrentState != EEnemyState::Idle) { return; }

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		EEnemyState::Range
	);

}

float AJuggernat::GetDamage()
{
	return StatsComp->Stats[EStat::Strength];
}

void AJuggernat::Attack()
{
	CombatComp->RandomAttack();
}

float AJuggernat::GetAnimDuration()
{
	return CombatComp->AnimDuration;
}

float AJuggernat::GetMeleeRange()
{
	return StatsComp->Stats[EStat::MeleeRange];
}

bool AJuggernat::IsDead() const
{
	if (StatsComp->Stats[EStat::Health] <= 0)
	{
		return true;
	}
	return false;
}

void AJuggernat::HandleDeath()
{
	float Duration{ PlayAnimMontage(DeathAnim) };

	ControllerRef->GetBrainComponent()
		->StopLogic("defeated");

	FindComponentByClass<UCapsuleComponent>()
		->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DestroyTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		DestroyTimerHandle,
		this,
		&AJuggernat::FinishDeathAnim,
		Duration,
		false
	);
}

void AJuggernat::FinishDeathAnim()
{
	Destroy();
}

void AJuggernat::PlayHurtAnim()
{
	PlayAnimMontage(HurtAnimMontage);
}




