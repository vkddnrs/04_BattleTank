// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
//#include "TankMovementComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>("TankMovementComponent");

	//UE_LOG(LogTemp, Warning, TEXT("DONKEY: ATank %s Constructor Cpp"), *GetName())

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY: ATank %s Begin_Play  Cpp"), *GetName())
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *HitLocation.ToString())
	if(!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}



void ATank::Fire()
{
	if (!ensure(ProjectileBlueprint || Barrel)) { return; }
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
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
		
	}
}
