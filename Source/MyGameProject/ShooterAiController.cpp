// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"

void AShooterAiController::BeginPlay() 
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAiController::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
/*  (JUST USE FOR ANOTHER METHOD FOR MOVING)
     APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

     if (LineOfSightTo(PlayerPawn))
     {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnowPosition"), PlayerPawn->GetActorLocation());

     }
     else
     {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));

    }
*/	
}

bool AShooterAiController::IsDead() const
{
    AShooter* ControlledCharacter = Cast<AShooter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }

    return true;

}
