// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class ETankFiringState : uint8
{
	RELOADING,
	AIMING,
	LOCKED_ON
};

class UTankBarrelSMC;
class UTurretSMC;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void UTankAimingComponent::BeginPlay() override;

	virtual void TickComponent(
		float deltaTime,
		enum ELevelTick tickType,
		FActorComponentTickFunction *thisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Input)
		void Initialise(UTankBarrelSMC* barrelToSet, UTurretSMC* turretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	void AimAtLocation(FVector hitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		ETankFiringState FiringState = ETankFiringState::RELOADING;

private:
	void MoveBarrel(FVector aimDirection);

	bool IsBarrelMoving();

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ProjectileLaunchVelocity = 40000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.;

	UTankBarrelSMC* BarrelMeshComponent = nullptr;
	UTurretSMC* TurretMeshComponent = nullptr;

	double LastFireTime = 0.;

	FVector AimDirection;
};
