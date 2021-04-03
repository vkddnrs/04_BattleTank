// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotation(float RelativeSpeed)
{
	// move the turret the right amount this frame
	// given the max rotation speed, and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RowNewRotation = GetRelativeRotation().Yaw + RotationChange;
	
	UE_LOG(LogTemp, Warning, TEXT("UTankTurret::Rotation() RelativeSpeed = %f"), RelativeSpeed)

	SetRelativeRotation(FRotator(0, RowNewRotation, 0));
	
}
