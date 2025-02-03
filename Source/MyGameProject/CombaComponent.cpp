#include "CombaComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainCharacter.h"

// Sets default values for this component's properties
UCombaComponent::UCombaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombaComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	// ...

}


// Called every frame
void UCombaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombaComponent::ComboAttack()
{
	if (CharacterRef->Implements<UMainCharacter>())
	{
		IMainCharacter* IPlayerRef{ Cast<IMainCharacter>(CharacterRef) };

		if (IPlayerRef && !IPlayerRef->HasEnoughStamina(StaminaCost))
		{
			return;
		}
	}

	if (!bPlayerCanAttack) { return; }

	bPlayerCanAttack = false;

	CharacterRef->PlayAnimMontage(AttackAnimation[ComboCounter]);

	ComboCounter++;

	int MaxCombo{ AttackAnimation.Num() };

	ComboCounter = UKismetMathLibrary::Wrap(
		ComboCounter,
		-1,
		(MaxCombo - 1)
	);

	OnAttackPerformedDelegate.Broadcast(StaminaCost);
}

void UCombaComponent::HandleResetAttack()
{
	bPlayerCanAttack = true;
}