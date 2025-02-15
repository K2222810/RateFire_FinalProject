// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.h"
#include "Figther.h"
#include "Shooter.generated.h"

class AGun; 

UCLASS()
class MYGAMEPROJECT_API AShooter : public ACharacter, public IMainCharacter, public IFigther
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class ULockOn* LockonComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAimComponent* AimComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTraceComponent* TraceComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCombaComponent* CombatComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStatsComponent* StatsComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBlockComponent* BlockComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPlayerActionsComponent* PlayerActionsComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	class UPlayerAnimationInstance* PlayerAnim;

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	void Shoot();
	private:
	void MoveForward(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void MoveRight(float AxisValue);

	void SwapUp(float slot);
	


	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float RotationRate = 10;

	UPROPERTY()
	AGun* CurrentGun[3];
	
	UPROPERTY(EditAnywhere)
	int32 ActiveIndex;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass[3];


	

	virtual float GetDamage() override;


	virtual bool HasEnoughStamina(float Cost) override;


/*
	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<TSubclassOf<AGun>> GunClasses;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	AGun* CurrentGun;
*/	
};
