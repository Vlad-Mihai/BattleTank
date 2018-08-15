// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerControlledTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank, it's %s"), *(PlayerTank->GetName()));
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* playerControlledTank = GetPlayerControlledTank();
	ATank* thisTank = GetSelfControlledTank();
	if (playerControlledTank && thisTank)
	{
		thisTank->AimAtLocation(playerControlledTank->GetActorLocation());
	}
}

ATank* ATankAIController::GetSelfControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerTank);
}
