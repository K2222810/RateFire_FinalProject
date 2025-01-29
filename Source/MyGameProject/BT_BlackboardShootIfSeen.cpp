// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_BlackboardShootIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBT_BlackboardShootIfSeen::UBT_BlackboardShootIfSeen()
{
    NodeName = "Shoot at Sight";
    
}

void UBT_BlackboardShootIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }

    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }


    
}