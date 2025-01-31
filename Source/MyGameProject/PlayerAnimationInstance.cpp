// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimationInstance.h"

void UPlayerAnimationInstance::UpdateVelocity()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef))
	{
		return;
	}

	FVector Velocity{ PawnRef->GetVelocity() };

	CurrentVelocity = static_cast<float>(Velocity.Length());

}

void UPlayerAnimationInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimationInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }

	if (!bIsInCombat) { return; }

	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}