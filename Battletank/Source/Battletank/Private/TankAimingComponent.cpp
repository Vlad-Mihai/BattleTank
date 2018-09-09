// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelSMC.h"
#include "TurretSMC.h "
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrelSMC* barrelToSet, UTurretSMC* turretToSet)
{
	BarrelMeshComponent = barrelToSet;
	TurretMeshComponent = turretToSet;
}

void UTankAimingComponent::AimAtLocation(FVector worldSpaceHitLocation, float projectileLaunchVelocity)
{
	if (!ensure(BarrelMeshComponent))
		return;

	FVector suggestedLaunchDirection;
	FVector startLocation = BarrelMeshComponent->GetSocketLocation(FName("ProjectileExitPoint"));
	
	if (UGameplayStatics::SuggestProjectileVelocity(
			this, 
			suggestedLaunchDirection,
			startLocation, 
			worldSpaceHitLocation,
			projectileLaunchVelocity, 
			false, 
			0, 
			0, 
			ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector aimDirection = suggestedLaunchDirection.GetSafeNormal();
		
		MoveBarrel(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	if (!ensure(BarrelMeshComponent) || !ensure(TurretMeshComponent))
		return;

	FRotator barrelRotator = BarrelMeshComponent->GetForwardVector().Rotation();
	FRotator aimDirectionAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimDirectionAsRotator - barrelRotator;

	BarrelMeshComponent->Elevate(deltaRotator.Pitch);
	TurretMeshComponent->Rotate(deltaRotator.Yaw);
}