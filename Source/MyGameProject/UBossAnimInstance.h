// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMEPROJECT_API UUBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentVelocity{ 0.0f };


	UFUNCTION(BlueprintCallable)
	void UpdateVelocity();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCharging{ false };

};
