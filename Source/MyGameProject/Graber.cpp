// Fill out your copyright notice in the Description page of Project Settings.


#include "Graber.h"
#include "Gun.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGraber::UGraber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGraber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGraber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGraber::Grab()
{	
	FHitResult HitResult;
	bool HasHit = GunTraceAmmo(HitResult);
	
	// Get the actor that owns the hit component
	AActor* HitActor = HitResult.GetActor();

	if (HasHit && HitActor && !HitActor->Tags.Contains("AmmoTaken"))
	{	
		// Tag the actor as "Grabbed"
		HitActor->Tags.Add("AmmoTaken");

		AGun* Gun = GetGunProperties(HitActor);

		if (Gun)
		{
			DrawDebugSphere(GetWorld(), HitResult.Location , 10, 10, FColor::Green, false, 5);
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);	
			ReloadAmmo(Gun); 
		}
	}
	else 
	{
		// Log that no hit was detected or no valid actor was found
        UE_LOG(LogTemp, Warning, TEXT("No valid hit or actor found during Grab operation."));

	}

}

bool UGraber::GunTraceAmmo(FHitResult &OutHit) const
{
	// Location of the actor component 
	FVector Start = GetComponentLocation();
	//multiples forwards distance to make an ending point
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	// Draws line 1. Location of the component use 2. the finish line 3. the color 
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	// Draws line 1. the target point 2.and 3. are sizes 4. the color 5. false means the sphere doesnt last forever 6. lifespan 
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	// Creates a sphere colission
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	// Performs a physics sweep test along a specified path to check for collisions. It returns true if it hits something, and false if it doesn't
	// Important, without sweep, HitResult doesn't know it just collided. It also updates the FHitResult structure with detailed information about the collision if a hit is detected.
	return GetWorld()->SweepSingleByChannel(
	//HitResult stores collision details. 
	OutHit,
	// Start and End define the path.
	Start, End,
	//
	FQuat::Identity,
	// ECC_GameTraceChannel1 specifies the collision channel to test.(you have to search in a  file)
	ECC_GameTraceChannel2,
	// Sphere defines the shape used for the sweep
	Sphere);

}

AGun* UGraber::GetGunProperties(AActor* Actor) const
{	
    	// Log the name of the actor's class
   	 	UE_LOG(LogTemp, Warning, TEXT("Hit actor class: %s"), *Actor->GetClass()->GetName());

    	// If you are looking for a specific type, for example AGun
   		 AGun* Gun = Cast<AGun>(Actor);

		return Gun;
	
} 

void UGraber::ReloadAmmo(AGun* Gun)
{
	Gun->Ammo += 10;
	// Log that the hit actor is of type AGun
    UE_LOG(LogTemp, Warning, TEXT("Ammo increased by 10. Current Ammo: %d"), Gun->Ammo);
   
}



