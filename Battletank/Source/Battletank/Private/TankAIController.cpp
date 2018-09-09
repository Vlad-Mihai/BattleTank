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

	auto playerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto thisTank = GetPawn();
	
	if (!ensure(playerControlledTank) || !ensure(thisTank))
		return;

	UTankAimingComponent* aimingComponent =
		thisTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent))
		return;

	aimingComponent->AimAtLocation(playerControlledTank->GetActorLocation());

	//aimingComponent->Fire();

	MoveToActor(playerControlledTank, 3000);
}