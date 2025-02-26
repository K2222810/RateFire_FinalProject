// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.h"
#include "EEnemyState.h"
#include "Figther.h"
#include "Juggernat.generated.h"

UCLASS()
class MYGAMEPROJECT_API AJuggernat : public ACharacter , public IEnemy , public IFigther
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnim;

	UPROPERTY(EditAnywhere)
	UAnimMontage* HurtAnimMontage;
	
	class AAIController* ControllerRef;


public:
	// Sets default values for this character's properties
	AJuggernat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombaComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTraceComponent* TraceComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* PawnDetected, APawn* PawnCheck);
	
	virtual float GetDamage() override;

	virtual void Attack() override;

	virtual float GetAnimDuration() override;

	virtual float GetMeleeRange() override;
	
	UFUNCTION()
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	UFUNCTION()
	void FinishDeathAnim();

	UFUNCTION(BlueprintCallable)
	void PlayHurtAnim();
	


};
