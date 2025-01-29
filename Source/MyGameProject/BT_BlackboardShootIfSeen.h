// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BT_BlackboardShootIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class MYGAMEPROJECT_API UBT_BlackboardShootIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBT_BlackboardShootIfSeen();
protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
	
	
};
