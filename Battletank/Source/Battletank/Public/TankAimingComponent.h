// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelSMC;
class UTurretSMC;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelMeshComponent(UTankBarrelSMC* barrelToSet);
	void SetTurretMeshComponent(UTurretSMC* turretToSet);

	void AimAtLocation(FVector worldSpaceLocation, float ProjectileLaunchVelocity);

private:
	void MoveBarrel(FVector aimDirection);

private:
	UTankBarrelSMC* BarrelMeshComponent = nullptr;
	UTurretSMC* TurretMeshComponent = nullptr;
};
