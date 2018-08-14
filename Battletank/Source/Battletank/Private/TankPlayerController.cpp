// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* controlledTank = GetControlledTank();
	if (!controlledTank)
		return;

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *hitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	return false;
}
