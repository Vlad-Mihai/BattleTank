// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelSMC.h"
#include "TurretSMC.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrelSMC* barrelToSet, UTurretSMC* turretToSet)
{
	BarrelMeshComponent = barrelToSet;
	TurretMeshComponent = turretToSet;
}

void UTankAimingComponent::TickComponent(
	float deltaTime,
	enum ELevelTick tickType,
	FActorComponentTickFunction *thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		if (IsBarrelMoving())
		{
			FiringState = ETankFiringState::AIMING;
		}
		else
		{
			FiringState = ETankFiringState::LOCKED_ON;
		}
	}
	else
	{
		FiringState = ETankFiringState::RELOADING;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(BarrelMeshComponent))
		return false;

	FVector barrelForwardVector = BarrelMeshComponent->GetForwardVector();

	return !barrelForwardVector.Equals(AimDirection);
}

void UTankAimingComponent::AimAtLocation(FVector worldSpaceHitLocation)
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
			ProjectileLaunchVelocity,
			false, 
			0, 
			0, 
			ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = suggestedLaunchDirection.GetSafeNormal();
		
		MoveBarrel(AimDirection);
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

void UTankAimingComponent::Fire()
{
	if (!ensure(BarrelMeshComponent) || !ensure(ProjectileBlueprint))
		return;

	if (FiringState == ETankFiringState::LOCKED_ON)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			BarrelMeshComponent->GetSocketLocation(FName("ProjectileExitPoint")),
			BarrelMeshComponent->GetSocketRotation(FName("ProjectileExitPoint")));
		
		projectile->LaunchProjectile(ProjectileLaunchVelocity);
		
		LastFireTime = FPlatformTime::Seconds();
	}
}