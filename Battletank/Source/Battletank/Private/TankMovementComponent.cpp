// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackSMC.h"

void UTankMovementComponent::Initialise(UTankTrackSMC* leftTrackToSet, UTankTrackSMC* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet)
		return;

	LeftTrack = leftTrackToSet;
	RightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), throwValue);

	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(throwValue);
}

void UTankMovementComponent::IntendTurnRight(float throwValue)
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(-throwValue);
}
