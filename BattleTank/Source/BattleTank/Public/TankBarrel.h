// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds barrel's properties and Elevate method
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxDegreesPerSecond = 10; // sensible default
	UPROPERTY(EditDefaultsOnly)
		float MaxElevationDegrees = 30; // sensible default
	UPROPERTY(EditDefaultsOnly)
		float MinElevationDegrees = -2; // sensible default
};
