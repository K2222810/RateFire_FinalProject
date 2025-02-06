// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimationInstance.h"
#include "Kismet/KismetMathLibrary.h" 

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

	// if (!bIsInCombat) { return; }

	FVector Velocity{ PawnRef->GetVelocity() };

	FTransform ActorTransform { PawnRef->GetActorTransform() };
	
	FVector LocalDirection = ActorTransform.InverseTransformVector(Velocity);

	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(LocalDirection);

	CurrentDirection = Rotation.Yaw;
}