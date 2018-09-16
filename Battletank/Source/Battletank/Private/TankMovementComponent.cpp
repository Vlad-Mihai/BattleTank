// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackSMC.h"

void UTankMovementComponent::Initialise(UTankTrackSMC* leftTrackToSet, UTankTrackSMC* rightTrackToSet)
{
	if (!ensure(leftTrackToSet) || !ensure(rightTrackToSet))
		return;

	LeftTrack = leftTrackToSet;
	RightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float throwValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), throwValue);

	if (!ensure(LeftTrack) || !ensure(RightTrack))
		return;

	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(throwValue);
}

void UTankMovementComponent::IntendTurnRight(float throwValue)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack))
		return;

	LeftTrack->SetThrottle(throwValue);
	RightTrack->SetThrottle(-throwValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("RDM ticking at %f."), FPlatformTime::Seconds());

	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = moveVelocity.GetSafeNormal();

	auto rightThrow = FVector::CrossProduct(tankForward, AIForwardIntention).Z;

	IntendTurnRight(rightThrow);

	/*if (rightThrow != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank moving would move right: %f"), rightThrow);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank doesn't want to move right."));
	}*/

	auto forwardThrow = FVector::DotProduct(tankForward, AIForwardIntention);

	IntendMoveForward(forwardThrow);

	/*if (forwardThrow != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank moving would move forward: %f"), forwardThrow);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank doesn't want to move forward."));
	}*/
}