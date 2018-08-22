// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackSMC.h"

void UTankTrackSMC::SetThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), throttle);
}


