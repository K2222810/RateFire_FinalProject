// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ClearBlackBoardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_ClearBlackBoardValue::UMyBTTask_ClearBlackBoardValue()
{
    NodeName = TEXT("Clear BlackBoard Value");

    // Create a unique instance of this node for each AI
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UMyBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
