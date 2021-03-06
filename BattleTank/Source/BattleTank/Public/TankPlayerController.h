// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim  
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

//****************************************************************************
public:
	virtual void SetPawn(APawn* InPawn) override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

	UFUNCTION()
		void OnPossesedTankDeath();

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

private:
	UTankAimingComponent* AimingComponent = nullptr;	
	
};
