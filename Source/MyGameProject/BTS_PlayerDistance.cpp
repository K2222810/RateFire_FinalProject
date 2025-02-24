// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_PlayerDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{	
    // Get the AI controller and its pawn
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController is null!"));
        return;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Pawn is null!"));
        return;
    }

    // Get the player's pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Pawn is null!"));
        return;
    }

    // Get the locations
    FVector CurrentLocation = AIPawn->GetActorLocation();
    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    // Calculate the distance
    float Distance = FVector::Distance(CurrentLocation, PlayerLocation);

	OwnerComp.GetBlackboardComponent()
		->SetValueAsFloat(TEXT("Distance"), Distance);

}

UBTS_PlayerDistance::UBTS_PlayerDistance()
{
	bCreateNodeInstance = true;
}
