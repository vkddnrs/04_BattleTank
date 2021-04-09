// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	
private:	
	

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	

	// Starts moving the barrel of the tank to where
	// the crosshairs intersect with the world.
	void AimTowardsCrosshair();
	
	// Return an Out parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairLocationX = 0.5;
	UPROPERTY(EditAnywhere)
		float CrossHairLocationY = 0.33333;
	UPROPERTY(EditAnywhere)
		int32 LineTraceRange = 1000000;


	
};
