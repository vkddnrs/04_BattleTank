// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }

	if (Throw)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);	
		//UE_LOG(LogTemp, Warning, TEXT("%s IntendMoveForward Throw %f"), *GetOwner()->GetName(), Throw)
	}
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }
	if(Throw)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
		//UE_LOG(LogTemp, Warning, TEXT("%s IntendMoveRight Throw %f"), *GetOwner()->GetName(), Throw)
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	
	IntendMoveForward(ForwardThrow);
	IntendMoveRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *GetOwner()->GetName(), *MoveVelocity.ToString())
}


