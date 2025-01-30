// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMEPROJECT_API UBTTaskNode_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	AAIController* ControllerRef;

	ACharacter* CharacterRef;

	class UUBossAnimInstance* BossAnim;

	UPROPERTY(EditAnywhere)
	float AcceptableRadius{ 100.0f };

	FScriptDelegate MoveCompletedDelegate;
	
	float OriginalWalkSpeed;

	UPROPERTY(EditAnywhere)
	float ChargeWalkSpeed{ 2000.0f };	

	bool bIsFinished{ false };

protected:
		virtual void TickTask ( 
			UBehaviorTreeComponent & OwnerComp,  
			uint8* NodeMemory, 
			float DeltaSeconds 
	) override;

public:
	UBTTaskNode_ChargeAttack();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;

	void ChargeAtPlayer();

	UFUNCTION()
	void HandleMoveCompleted();

	UFUNCTION()
	void FinishAttackTask();
	
};
