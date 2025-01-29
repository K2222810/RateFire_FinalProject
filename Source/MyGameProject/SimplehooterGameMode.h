// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimplehooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMEPROJECT_API ASimplehooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
public: 
	virtual void PawnKilled(APawn* PawnKilled);
	
	
};
