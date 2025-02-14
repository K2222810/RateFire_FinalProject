// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAMEPROJECT_API UAimComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	// Sets default values for this component's properties
	UAimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Start aiming (e.g., zooms the camera in)
	UFUNCTION(BlueprintCallable)
	void StartAiming(float ZoomAmount);

	// Stop aiming (e.g., zooms the camera out)
	UFUNCTION(BlueprintCallable)
	void StopAiming(float ZoomAmount);

	// Toggle aiming state (zooms in or out)
	UFUNCTION(BlueprintCallable)
	void ToggleAiming(float ZoomAmount);

private:
	// Reference to the owning actor
	UPROPERTY()
	ACharacter* OwnerRef;

	// Reference to the player's controller
	UPROPERTY()
	APlayerController* Controller;

	// Reference to the spring arm component (used for camera handling)
	UPROPERTY()
	class USpringArmComponent* SpringArmComp;

	// Tracks if the player is currently aiming
	UPROPERTY(VisibleAnywhere)
	bool bIsAiming = false;
		
};
