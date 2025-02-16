// Fill out your copyright notice in the Description page of Project Settings.


#include "Juggernat.h"
#include "StatsComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AJuggernat::AJuggernat()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));


}

// Called when the game starts or when spawned
void AJuggernat::BeginPlay()
{	
	Super::BeginPlay();


	BlackboardComp = GetController<AAIController>()->GetBlackboardComponent();

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

