// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelSMC.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

void UTankBarrelSMC::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1., 1.);

	float elevationChange = 
		relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float clampedNewElevation = 
		FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(clampedNewElevation, 0., 0.));
}


