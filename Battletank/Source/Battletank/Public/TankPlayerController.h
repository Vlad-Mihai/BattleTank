// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* aimingComponent);

private:
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetHitLocationByDirection(FVector lookDirection, FVector& hitLocation) const;

private:
	UPROPERTY(EditAnywhere)
		float CrosshairXPosition = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYPosition = 0.33333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
};
