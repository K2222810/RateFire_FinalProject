#include "AimComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UAimComponent::UAimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAimComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the owner of this component
	OwnerRef = Cast<ACharacter>(GetOwner());
	if (!OwnerRef) return;

	// Get the player controller
	Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	// Find the spring arm component in the owner
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
	if (!SpringArmComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpringArmComponent not found in %s"), *OwnerRef->GetName());
	}
}

// Called every frame
void UAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Add any logic here if needed during runtime
}

// Starts aiming (zooms the camera forward)
void UAimComponent::StartAiming(float ZoomAmount)
{
	if (!SpringArmComp) return;

	// Adjust the SpringArm's TargetArmLength to zoom forward
	float NewArmLength = FMath::Clamp(SpringArmComp->TargetArmLength - ZoomAmount, 100.0f, 600.0f);
	SpringArmComp->TargetArmLength = NewArmLength;

	// Adjust the offset to ensure the camera moves slightly forward
	FVector ForwardOffset = OwnerRef->GetActorForwardVector() * 50.0f; // Move forward by 50 units
	SpringArmComp->TargetOffset = ForwardOffset;

	// Set aiming flag
	bIsAiming = true;

	UE_LOG(LogTemp, Log, TEXT("Aiming started. TargetArmLength: %f, Offset: %s"), SpringArmComp->TargetArmLength, *ForwardOffset.ToString());
}

// Stops aiming (resets the camera zoom and offset)
void UAimComponent::StopAiming(float ZoomAmount)
{
	if (!SpringArmComp) return;

	// Adjust the SpringArm's TargetArmLength to zoom out
	float NewArmLength = FMath::Clamp(SpringArmComp->TargetArmLength + ZoomAmount, 100.0f, 600.0f);
	SpringArmComp->TargetArmLength = NewArmLength;

	// Reset the offset to the default
	SpringArmComp->TargetOffset = FVector::ZeroVector;

	// Clear aiming flag
	bIsAiming = false;

	UE_LOG(LogTemp, Log, TEXT("Aiming stopped. TargetArmLength: %f"), SpringArmComp->TargetArmLength);
}

// Toggles aiming (zooms forward and resets as needed)
void UAimComponent::ToggleAiming(float ZoomAmount)
{
	if (bIsAiming)
	{
		StopAiming(ZoomAmount);
	}
	else
	{
		StartAiming(ZoomAmount);
	}
}
