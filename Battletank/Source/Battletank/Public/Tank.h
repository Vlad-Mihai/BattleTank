// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelMeshComponent(UTankBarrelSMC* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretMeshComponent(UTurretSMC* turretToSet);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UTankAimingComponent* AimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float ProjectileLaunchVelocity = 70000;
};
