// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MeleeAttack.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Figther.h"
#include "GameFramework/Character.h"
#include "EEnemyState.h"

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsFinished = false;

	float Distance{
		OwnerComp.GetBlackboardComponent()
			->GetValueAsFloat(TEXT("Distance"))
	};

	AAIController* AIRef{ OwnerComp.GetAIOwner() };

	if (Distance > AttackRadius) {
		APawn* PlayerRef{
			GetWorld()->GetFirstPlayerController()->GetPawn()
		};
		FAIMoveRequest MoveRequest{ PlayerRef };
		MoveRequest.SetUsePathfinding(true);
		MoveRequest.SetAcceptanceRadius(AcceptableRadius);
		
		AIRef->ReceiveMoveCompleted.AddUnique(
			MoveDelegate);

		AIRef->MoveTo(MoveRequest);
		AIRef->SetFocus(PlayerRef);


		
	}
	else {
		IFigther* FigtherRef{
			Cast<IFigther>(
				AIRef->GetCharacter()
			)
		};

		FigtherRef->Attack();

		FTimerHandle AttackTimerHandle;

		AIRef->GetCharacter()->GetWorldTimerManager().SetTimer(
			AttackTimerHandle,
			this,
			&UBTT_MeleeAttack::FinishAttackTask,
			FigtherRef->GetAnimDuration(),
			false
		);

	}



	return EBTNodeResult::InProgress;

}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	float Distance{
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"))
	};

	AAIController* AIRef{ OwnerComp.GetAIOwner() };

	IFigther* FigtherRef{
		Cast<IFigther>(AIRef->GetCharacter())
	};

	if (Distance > FigtherRef->GetMeleeRange()) {

		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(
			TEXT("CurrentState"), EEnemyState::Range
		);

		AbortTask(OwnerComp, NodeMemory);

		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);

		AIRef->StopMovement();
		AIRef->ClearFocus(EAIFocusPriority::Gameplay);

		AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
	}

	if (!bIsFinished) {
		return;
	}

	OwnerComp.GetAIOwner()->ReceiveMoveCompleted.Remove(MoveDelegate);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
	MoveDelegate.BindUFunction(this, "FinishAttackTask");

	bNotifyTick = true;

	// Create a unique instance of this node for each AI
	bCreateNodeInstance = true;
}

void UBTT_MeleeAttack::FinishAttackTask()
{
	bIsFinished = true;
}



