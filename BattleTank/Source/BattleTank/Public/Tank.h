// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
 //************************************************

public:
	UFUNCTION(BlueprintCallable)
	void Fire();
	
private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000; // projectile starting speed 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	

protected:
	//UPROPERTY(BlueprintReadOnly, Category = Setup)
	//UTankAimingComponent* TankAimingComponent = nullptr;
	
	//UPROPERTY(BlueprintReadOnly, Category = Setup)
	//	UTankMovementComponent* TankMovementComponent = nullptr;
	
	UTankBarrel* Barrel = nullptr;						// local barrel reference for spawning projectile
	

	
	//UTankTrack* LeftTrack = nullptr;
	//UTankTrack* RightTrack = nullptr;
};
