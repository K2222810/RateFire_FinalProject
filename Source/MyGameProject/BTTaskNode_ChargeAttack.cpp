#include "BTTaskNode_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "UBossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTTaskNode_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge{
		OwnerComp.GetBlackboardComponent()
			->GetValueAsBool(TEXT("IsReadyToCharge"))
	};

	if (bIsReadyToCharge)
	{
		OwnerComp.GetBlackboardComponent()
			->SetValueAsBool(
				TEXT("IsReadyToCharge"), false
			);

		ChargeAtPlayer();
	}

	if (!bIsFinished) { return; }

	ControllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

UBTTaskNode_ChargeAttack::UBTTaskNode_ChargeAttack()
{
	bNotifyTick = true;

	MoveCompletedDelegate.BindUFunction(
		this, "HandleMoveCompleted"
	);

}

EBTNodeResult::Type UBTTaskNode_ChargeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();
	BossAnim = Cast<UUBossAnimInstance>(
		CharacterRef->GetMesh()->GetAnimInstance()
	);

	BossAnim->bIsCharging = true;

	OwnerComp.GetBlackboardComponent()
		->SetValueAsBool(
			TEXT("IsReadyToCharge"), false
		);

	bIsFinished = false;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_ChargeAttack::ChargeAtPlayer()
{
	APawn* PlayerRef{
		GetWorld()->GetFirstPlayerController()->GetPawn()
	};
	FVector PlayerLocation{ PlayerRef->GetActorLocation() };

	FAIMoveRequest MoveRequest{ PlayerLocation };
	MoveRequest.SetUsePathfinding(true);
	MoveRequest.SetAcceptanceRadius(AcceptableRadius);

	ControllerRef->MoveTo(MoveRequest);
	ControllerRef->SetFocus(PlayerRef);

	ControllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);

	OriginalWalkSpeed = CharacterRef->GetCharacterMovement()
		->MaxWalkSpeed;

	CharacterRef->GetCharacterMovement()
		->MaxWalkSpeed = ChargeWalkSpeed;


}

void UBTTaskNode_ChargeAttack::HandleMoveCompleted()
{

	BossAnim->bIsCharging = false;

	FTimerHandle AttackTimerHandle;

	CharacterRef->GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&UBTTaskNode_ChargeAttack::FinishAttackTask,
		1.0f,
		false
	);

	CharacterRef->GetCharacterMovement()
		->MaxWalkSpeed = OriginalWalkSpeed;



}

void UBTTaskNode_ChargeAttack::FinishAttackTask()
{

	bIsFinished = true;

	UE_LOG(LogTemp, Warning, TEXT("Task Finished!"));
}
