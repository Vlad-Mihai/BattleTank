// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretSMC.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTurretSMC : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotationDegrees = 360;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinRotationDegrees = -360;
};
