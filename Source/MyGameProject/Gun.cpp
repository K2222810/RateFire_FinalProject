// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::PullTrigger()
{		
	
	if(HasAmmo(Ammo)) {

		Ammo--;
		UE_LOG(LogTemp, Warning, TEXT("Current Ammo: %d"), Ammo);

		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	
		

		FVector ShootDirection;
		FHitResult OutHit;
		bool bSuccess =  GunTrace(OutHit,ShootDirection);
		if (bSuccess )
		{
		
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BulletHole,OutHit.Location,ShootDirection.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutHit.Location);

			AActor* HitActor = OutHit.GetActor();
			if (HitActor != nullptr)
			{	
				FPointDamageEvent DamageEvent(Damage, OutHit, ShootDirection, nullptr);
				AController* OwnerController = GetOwnerController();
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);

			} 
		}
	}
	else 
	{
		UGameplayStatics::SpawnSoundAttached(OutAmmoSound, Mesh, TEXT("MuzzleFlashSocket"));
	
	}
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult &OutHit, FVector& ShootDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShootDirection = -Rotation.Vector();
	
	FVector start = Location;
	FVector End = Location + Rotation.Vector() * MaxRange; 

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());


	return GetWorld()->LineTraceSingleByChannel(OutHit, start, End, ECollisionChannel::ECC_GameTraceChannel1,Params);

}

AController* AGun::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}

bool AGun::HasAmmo(int32 Amunition)
{	
	if(Amunition > 0)
	{	
		return Amunition > 0;
	}
	else
	{
		return Amunition < 0;
	}
} 

void AGun::ReloadAmmo()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading"));	

	Ammo = DefaultAmmo;
	
}



