// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//***************************************************************


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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure(Barrel || Turret)) { return; }
	// work-out difference between current barrel rotation, and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	float AngleBurrelRotation = AimAsRotator.Pitch - BarrelRotator.Pitch;
	float AngleTurretRotation = AimAsRotator.Yaw - BarrelRotator.Yaw;
	
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *AimAsRotator.ToString())

	Barrel->Elevate(AngleBurrelRotation);
	Turret->Rotation(AngleTurretRotation);
}

