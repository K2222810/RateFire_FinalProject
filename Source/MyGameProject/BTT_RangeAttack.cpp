// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "EEnemyState.h"
EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{
		OwnerComp.GetAIOwner()->GetPawn<ACharacter>()
	};

	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	CharacterRef->PlayAnimMontage(AnimMontage);

	return EBTNodeResult::Succeeded;

}
