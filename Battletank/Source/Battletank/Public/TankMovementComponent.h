// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackSMC;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float throwValue);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float throwValue);
	
	UFUNCTION(BlueprintCallable, Category = Input)
		void Initialise(UTankTrackSMC* leftTrackToSet, UTankTrackSMC* rightTrackToSet);

private:
	UTankTrackSMC* LeftTrack = nullptr;
	UTankTrackSMC* RightTrack = nullptr;
};
