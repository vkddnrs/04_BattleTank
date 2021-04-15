// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	AmmoOut
};

class UTankTurret;
class UTankBarrel;
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//************************************************************

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
	
	inline EFiringState GetFiringState() const;
	inline int32 GetAmmoCount() const;

private:
  	UTankBarrel* Barrel = nullptr; // ствол пушки
	UTankTurret* Turret = nullptr; // башня

	FVector AimDirection = FVector();

	void MoveBarrelTowards();
	bool IsBarrelMoving();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Firing")
	int32 AmmoCount = 20;

	UPROPERTY(EditAnywhere, Category = "Firing")
	  float LaunchSpeed = 4000; // projectile starting speed
	UPROPERTY(BlueprintReadOnly, Category = "State")
	  EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	
};


