// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Graber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAMEPROJECT_API UGraber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGraber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();
	
	private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100;		

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	bool GunTraceAmmo(FHitResult& OutHiteResult) const; 

	class AGun* GetGunProperties(AActor* Actor) const;

	void ReloadAmmo(AGun* Gun); 	 	
};
