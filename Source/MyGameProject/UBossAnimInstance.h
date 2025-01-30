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
	float CurrentSpeed{ 0.0f };
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCharging{ false };

};
