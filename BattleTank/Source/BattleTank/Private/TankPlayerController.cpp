// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "BattleTank/Public/TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());	
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if(ensure(AimComponent))
	{
		FoundAimingComponent(AimComponent);
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController find aiming component at Begin Play"))
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController can't find aiming component at Begin Play"))
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController not posessing tank"))
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString())
		// Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

// Get world location if linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString())	
	
	// "De-project" the screen position of the crosshair to a world direction (LookDirection)
	FVector CameraWorldLocation;
	FVector LookDirection;
	if(DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		FHitResult HitResult;
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
		
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
		{
			HitLocation = HitResult.Location;
			return true;
		}
		HitLocation = FVector(0.f);
		return true;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *LookDirection.ToString())
	
	
	return false;
}
