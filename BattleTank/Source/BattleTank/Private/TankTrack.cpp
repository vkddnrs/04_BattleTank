// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the slippage speed   - вычислить скорость скольжения
	auto SlippegeSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Work-out the required acceleration  this frame to correct
	auto CorrectionAcceleration = -SlippegeSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways for (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 4; // Two tracks
	
	TankRoot->AddForce(CorrectionForce);

	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce : %s"), *CorrectionForce.ToString())
}

void UTankTrack::SetThrottle(float Throttle)
{
	if(!ensure(this)) { return; }
	
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle %f"), *GetName(), Throttle)

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ForceApplied : %s, ForceLocation : %s"), *ForceApplied.ToString(), *ForceLocation.ToString())
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpuls, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"))
}