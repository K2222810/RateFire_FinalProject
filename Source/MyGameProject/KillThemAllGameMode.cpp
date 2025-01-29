// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAiController.h"

void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("A pawn was killed!"));
    
    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(PawnKilled->GetController());
    if (ShooterPlayerController != nullptr)
    {
       EndGame(false);
    }

    for (AShooterAiController* AIController : TActorRange<AShooterAiController>(GetWorld()))
    {
        if (!AIController->IsDead())
        {
            return;
        }
    }
    
    EndGame(true);

} 
void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner) 
{
     for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }

}

