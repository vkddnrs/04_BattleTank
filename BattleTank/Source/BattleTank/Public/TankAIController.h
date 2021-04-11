// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
  //*********************************************

protected:
	UPROPERTY(EditAnywhere, Category = AISetup)
	float AcceptanceRadius = 300; // Yow close can the AI tank get

	UTankAimingComponent* AimComponent = nullptr;
	//ATank* PlayerTank = nullptr;
	//ATank* ControlledTank = nullptr;
        
		
};
