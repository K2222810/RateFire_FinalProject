// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "Shooter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = "Shoot";

    // Create a unique instance of this node for each AI
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
   
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AShooter* Character = Cast<AShooter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    Character->Shoot(); 
    return EBTNodeResult::Succeeded;
}