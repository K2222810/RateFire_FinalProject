// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOn.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	// Name of the event 
	FOnUpdatedTargetSignature,
	// the class contains the variable
	ULockOn,
	// Variable name
	OnUpdatedTargetDelegate,
	// Type of varaible
	AActor*,
	// Name of the parameter
	NewTargetActorRef

);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAMEPROJECT_API ULockOn : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerRef;

	APlayerController* Controller;

	class UCharacterMovementComponent* MovementComp;

	class USpringArmComponent* SpringArmComp;

public:
	// Sets default values for this component's properties
	ULockOn();
	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockon(float radius = 750.f);

	UFUNCTION(BlueprintCallable)
	void StopLockon();

	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float radius = 750.f);

	UPROPERTY(EditAnywhere)
	double BreakDistance{ 1000.0 };


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
