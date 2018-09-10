// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* aimingComponent = 
		GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComponent))
	{
		FoundAimingComponent(aimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	APawn* controlledTank = GetPawn();
	
	if (!controlledTank)
		return;

	UTankAimingComponent* aimingComponent =
		controlledTank->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(aimingComponent))
		return;

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		aimingComponent->AimAtLocation(hitLocation);
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
		if (GetHitLocationByDirection(worldDirection, hitLocation))
		{
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetHitLocationByDirection(FVector lookDirection, FVector& hitLocation) const
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