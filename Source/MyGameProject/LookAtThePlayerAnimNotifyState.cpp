// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtThePlayerAnimNotifyState.h"
#include "LookAtPlayerComponent.h"

void ULookAtThePlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AActor* OwnerRef{ MeshComp->GetOwner() };

	if (!IsValid(OwnerRef)) { return; }

	ULookAtPlayerComponent* RotationComp{
		OwnerRef->FindComponentByClass<ULookAtPlayerComponent>()
	};

	if (!IsValid(RotationComp)) { return; }

	RotationComp->bCanRotate = true;
}

void ULookAtThePlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AActor* OwnerRef{ MeshComp->GetOwner() };

	if (!IsValid(OwnerRef)) { return; }

	ULookAtPlayerComponent* RotationComp{
		OwnerRef->FindComponentByClass<ULookAtPlayerComponent>()
	};

	if (!IsValid(RotationComp)) { return; }

	RotationComp->bCanRotate = false;
}
