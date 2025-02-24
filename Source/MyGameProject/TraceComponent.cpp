// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Figther.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	skeletalComp = GetOwner()
		->FindComponentByClass<USkeletalMeshComponent>();


}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttacking) { return; }

	TArray<FHitResult> AllResults;

	for (const FTraceSockets Socket : Sockets) {
		FVector StartSocketLocation{
			skeletalComp->GetSocketLocation(Socket.Start)
		};
		FVector EndSocketLocation{
			skeletalComp->GetSocketLocation(Socket.End)
		};
		FQuat ShapeRotation{
			skeletalComp->GetSocketQuaternion(Socket.Rotation)
		};

		TArray<FHitResult> OutResults;
		double WeaponDistance{
			FVector::Distance(StartSocketLocation, EndSocketLocation)
		};
		FVector BoxHalfExtent{
			BoxCollisionLength, BoxCollisionLength, WeaponDistance
		};
		BoxHalfExtent /= 2; // BoxHalfExtent = BoxHalfExtent / 2;
		FCollisionShape Box{
			FCollisionShape::MakeBox(BoxHalfExtent)
		};
		FCollisionQueryParams IgnoreParams{
			FName { TEXT("Ignore Params") },
			false,
			GetOwner()
		};

		bool bHasFoundTargets{ GetWorld()->SweepMultiByChannel(
			OutResults,
			StartSocketLocation,
			EndSocketLocation,
			ShapeRotation,
			ECollisionChannel::ECC_GameTraceChannel3,
			Box,
			IgnoreParams
		) };

		for (FHitResult Hit : OutResults) {
			AllResults.Add(Hit);
		}

		if (bDebugMode)
		{
			FVector CenterPoint{
				UKismetMathLibrary::VLerp(
					StartSocketLocation, EndSocketLocation, 0.5f
				)
			};

			UKismetSystemLibrary::DrawDebugBox(
				GetWorld(),
				CenterPoint,
				Box.GetExtent(),
				bHasFoundTargets ? FLinearColor::Green : FLinearColor::Red,
				ShapeRotation.Rotator(),
				1.0f,
				2.0f
			);
		}
	}

	if (AllResults.Num() == 0) { return; }

	float CharacterDamage{ 0.0f };

	IFigther* FighterRef{ Cast<IFigther>(GetOwner()) };

	if (FighterRef)
	{
		CharacterDamage = FighterRef->GetDamage();
	}

	FDamageEvent TargetAttackedEvent;

	for (const FHitResult& Hit : AllResults)
	{
		AActor* TargetActor{ Hit.GetActor() };

		if (TargetsToIgnore.Contains(TargetActor)) { continue; }

		TargetActor->TakeDamage(
			CharacterDamage,
			TargetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
		);

		TargetsToIgnore.AddUnique(TargetActor);

		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticleTemplate,
			Hit.ImpactPoint
		);



	}
}


void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}


