// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("AI Controller ticking."));

	auto playerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto thisTank = GetPawn();
	
	if (!ensure(playerControlledTank) || !ensure(thisTank))
		return;

	//UE_LOG(LogTemp, Warning, TEXT("AI Controller wanting to move to: [%f,%f,%f]."), playerControlledTank->GetActorLocation().X, playerControlledTank->GetActorLocation().Y, playerControlledTank->GetActorLocation().Z);

	MoveToActor(playerControlledTank, ProximityAcceptanceRadius);

	UTankAimingComponent* aimingComponent =
		thisTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent))
		return;

	aimingComponent->AimAtLocation(playerControlledTank->GetActorLocation());

	if (aimingComponent->GetFiringState() == ETankFiringState::LOCKED_ON)
	{
		aimingComponent->Fire();
	}
}