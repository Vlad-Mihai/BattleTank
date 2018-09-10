// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackSMC.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackSMC : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrackSMC();

	virtual void BeginPlay() override;

private:
	void ApplyCorrectingSideForce();

	void DriveTrack();

	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComponent, 
			FVector NormalImpulse, 
			const FHitResult& Hit);

public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float throttle);

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
		float MaxDrivingForce = 400000;

private:
	float CurrentThrottle = 0.;
};
