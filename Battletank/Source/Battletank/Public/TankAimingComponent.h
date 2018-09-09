// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	RELOADING,
	AIMING,
	LOCKED
};

class UTankBarrelSMC;
class UTurretSMC;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Input)
		void Initialise(UTankBarrelSMC* barrelToSet, UTurretSMC* turretToSet);

	void AimAtLocation(FVector hitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::RELOADING;

private:
	void MoveBarrel(FVector aimDirection);

private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float ProjectileLaunchVelocity = 70000;

	UTankBarrelSMC* BarrelMeshComponent = nullptr;
	UTurretSMC* TurretMeshComponent = nullptr;
};
