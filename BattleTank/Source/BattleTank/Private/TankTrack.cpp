// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplaySidewaysForce()
{
	// Calculate the slippage speed   - вычислить скорость скольжения
	auto SlippegeSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration  this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippegeSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways for (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 4; // Two tracks
	
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce : %s"), *CorrectionForce.ToString())
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetOwner()->GetActorForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ForwardVector : %s"), *GetOwner()->GetActorForwardVector().ToString())
}

void UTankTrack::SetThrottle(float Throttle)
{
	if(!ensure(this)) { return; }
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpuls, const FHitResult& Hit)
{
	DriveTrack();
	//ApplaySidewaysForce();	
	
	CurrentThrottle = 0;
	//UE_LOG(LogTemp, Warning, TEXT("A'm hit!"))
}