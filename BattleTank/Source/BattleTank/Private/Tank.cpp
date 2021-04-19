// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>("TankMovementComponent");

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////

inline float ATank::GetHealthPercent() const
{
	return  CurrentHealth / Health;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Damage to %s:  DamageAmount = %f	DamageToApply = %f"), *GetName(), DamageAmount, DamageToApply)

	if(CurrentHealth <= 0.0)
		UE_LOG(LogTemp, Warning, TEXT("%s is died"), *GetName())
	
	return DamageToApply;
}





