// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "Figther.h"
#include "EEnemyState.h"
	
UBTT_RangeAttack::UBTT_RangeAttack()
{
	// Create a unique instance of this node for each AI
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{
		OwnerComp.GetAIOwner()->GetPawn<ACharacter>()
	};

	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	float Distance{
		OwnerComp.GetBlackboardComponent()
			->GetValueAsFloat(TEXT("Distance"))
	};

	IFigther* FigtherRef{ Cast<IFigther>(CharacterRef) };

	if (Distance < FigtherRef->GetMeleeRange())

	{
		OwnerComp.GetBlackboardComponent()
			->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Melee);

		AbortTask(OwnerComp, NodeMemory);

		return EBTNodeResult::Aborted;
	}

	CharacterRef->PlayAnimMontage(AnimMontage);

	double RandomValue{ UKismetMathLibrary::RandomFloat() };

	if (RandomValue > Threshold)
	{
		Threshold = 0.9;

		OwnerComp.GetBlackboardComponent()
			->SetValueAsEnum(
				TEXT("CurrentState"),
				EEnemyState::Charge
			);
	}
	else
	{
		Threshold -= 0.1;
	}

	return EBTNodeResult::Succeeded;



}
