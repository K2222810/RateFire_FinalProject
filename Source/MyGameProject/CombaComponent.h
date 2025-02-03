// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature,
	UCombaComponent, OnAttackPerformedDelegate,
	float, Amount
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAMEPROJECT_API UCombaComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackAnimation;

	ACharacter* CharacterRef;

	UPROPERTY(VisibleAnywhere)
	int ComboCounter{ 0 };

	UPROPERTY(VisibleAnywhere)
	bool bPlayerCanAttack{ true };

	UPROPERTY(EditAnywhere)
	float StaminaCost{ 5.0 };

public:
	// Sets default values for this component's properties
	UCombaComponent();

	UPROPERTY(BlueprintAssignable)
	FOnAttackPerformedSignature OnAttackPerformedDelegate;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ComboAttack();

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();
		
};
