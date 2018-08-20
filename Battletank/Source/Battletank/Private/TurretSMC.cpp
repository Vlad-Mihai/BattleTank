// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretSMC.h"


void UTurretSMC::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1., 1.);

	float rotationChange =
		relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewRotation = RelativeRotation.Yaw + rotationChange;
	float clampedNewRotation =
		FMath::Clamp<float>(rawNewRotation, MinRotationDegrees, MaxRotationDegrees);
	
	SetRelativeRotation(FRotator(0., clampedNewRotation, 0.));
}