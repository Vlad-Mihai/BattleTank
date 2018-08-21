// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrelSMC.h"
#include "Projectile.h"
#include "TankBarrelSMC.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
	if (!BarrelRefference)
		return;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			BarrelRefference->GetSocketLocation(FName("ProjectileExitPoint")),
			BarrelRefference->GetSocketRotation(FName("ProjectileExitPoint")));

		projectile->LaunchProjectile(ProjectileLaunchVelocity);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAtLocation(FVector hitLocation)
{
	AimingComponent->AimAtLocation(hitLocation, ProjectileLaunchVelocity);
}

void ATank::SetBarrelMeshComponent(UTankBarrelSMC* barrelToSet)
{
	AimingComponent->SetBarrelMeshComponent(barrelToSet);

	BarrelRefference = barrelToSet;
}

void ATank::SetTurretMeshComponent(UTurretSMC* turretToSet)
{
	AimingComponent->SetTurretMeshComponent(turretToSet);
}
