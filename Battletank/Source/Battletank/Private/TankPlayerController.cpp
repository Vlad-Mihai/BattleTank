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

	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = 
		FVector2D(viewportSizeX * CrosshairXPosition, viewportSizeY * CrosshairYPosition);

	FVector worldDirection;
	FVector cameraWorldLocation; // not needed at this time
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, worldDirection))
	{
		if (GetHitLocationByDrection(worldDirection, hitLocation))
		{
			ATank* controlledTank = GetControlledTank();
			if (!controlledTank)
				return false;

			controlledTank->AimAtLocation(hitLocation);
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetHitLocationByDrection(FVector lookDirection, FVector& hitLocation) const
{
	FHitResult hitResult;
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = cameraLocation + lookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult, 
		cameraLocation, 
		endLocation, 
		ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	return false;
}