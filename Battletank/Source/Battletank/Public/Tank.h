// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAtLocation(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* AimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float ProjectileLaunchVelocity = 70000;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.;

	UTankBarrelSMC* BarrelRefference = nullptr;

	double LastFireTime = 0.;
};
