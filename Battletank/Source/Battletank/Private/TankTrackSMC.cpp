// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackSMC.h"

UTankTrackSMC::UTankTrackSMC()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTankTrackSMC::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrackSMC::OnHit);
}

void UTankTrackSMC::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetOwner()->GetName(), CurrentThrottle);

	DriveTrack();
	ApplyCorrectingSideForce();

	CurrentThrottle = 0.;
}

void UTankTrackSMC::ApplyCorrectingSideForce()
{
	// Stopping the tank from sliding sideways
	float lateralSlidingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	float deltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctingAcceleration = -((lateralSlidingSpeed / deltaTime) * GetRightVector());
	UStaticMeshComponent* rootTank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	float tankMass = rootTank->GetMass();
	FVector correctingForce = (tankMass * correctingAcceleration) / 2;

	rootTank->AddForce(correctingForce);
}

void UTankTrackSMC::SetThrottle(float throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetOwner()->GetName(), throttle);

	CurrentThrottle = FMath::Clamp<float>(throttle, -1., 1.);
}

void UTankTrackSMC::DriveTrack()
{
	FVector forceApplied = CurrentThrottle * GetForwardVector() * MaxDrivingForce;
	FVector trackLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, trackLocation);
}


