// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoCount <= 0) { return; }

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		FiringState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		FiringState = EFiringState::Aiming;
	else
		FiringState = EFiringState::Locked;
}

//***************************************************************

inline EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

inline int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(const FVector WorldSpaceAim)
{
	if(!ensure(Barrel))	{ return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("Projectile");	

	// Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			WorldSpaceAim,
			LaunchSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace/*,
			FCollisionResponseParams(),
			TArray < AActor* >(),
			true*/
		))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if(!ensure(Barrel || Turret)) { return; }
	// work-out difference between current barrel rotation, and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	float AngleBurrelRotation = AimAsRotator.Pitch - BarrelRotator.Pitch;
	float AngleTurretRotation = AimAsRotator.Yaw - BarrelRotator.Yaw;
	
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *AimAsRotator.ToString())

	Barrel->Elevate(AngleBurrelRotation);

	if (AngleTurretRotation > 180)
		AngleTurretRotation = AngleTurretRotation - 360;
	
	Turret->Rotation(AngleTurretRotation);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBlueprint) || !ensure(Barrel)) { return; }

	if (AmmoCount <= 0 ) { return; }

	if (FiringState != EFiringState::Reloading)
	{
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketTransform("Projectile")
			//Barrel->GetSocketLocation("Projectile"),
			//Barrel->GetSocketRotation("Projectile")
			);


		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoCount--;
		if (AmmoCount == 0)
			FiringState = EFiringState::AmmoOut;

	}
}




bool UTankAimingComponent::IsBarrelMoving()
{
	if(!ensure(Barrel)) { return false; }
	if (!AimDirection.Equals(Barrel->GetForwardVector(), 0.01))
		return true;
	else
		return false;
}