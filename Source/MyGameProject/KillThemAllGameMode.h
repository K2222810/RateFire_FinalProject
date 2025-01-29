// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplehooterGameMode.h"
#include "KillThemAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMEPROJECT_API AKillThemAllGameMode : public ASimplehooterGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
