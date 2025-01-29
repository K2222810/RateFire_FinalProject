// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) 
{   
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    CrossHead->RemoveFromParent();
    if (bIsWinner)
    {
       UUserWidget* WinScreen = CreateWidget(this, WinProcess);
            if (WinScreen != nullptr)
            {
                WinScreen->AddToViewport();
            }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
            if (LoseScreen != nullptr)
            {
                LoseScreen->AddToViewport();
            }
    }
     
    

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}


void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

    CrossHead = CreateWidget(this, Cross);
        if (CrossHead != nullptr)
        {
            CrossHead->AddToViewport();
        }
}