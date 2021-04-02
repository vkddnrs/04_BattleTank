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
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 2; // sensible default
	UPROPERTY(EditAnywhere)
		float MaxElevationDegrees = 30; // sensible default
	UPROPERTY(EditAnywhere)
		float MinElevationDegrees = -2; // sensible default
};
