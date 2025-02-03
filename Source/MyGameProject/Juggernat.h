// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.h"
#include "EEnemyState.h"
#include "Juggernat.generated.h"

UCLASS()
class MYGAMEPROJECT_API AJuggernat : public ACharacter , public IEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent* BlackboardComp;

public:
	// Sets default values for this character's properties
	AJuggernat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* StatsComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* PawnDetected, APawn* PawnCheck);

};
