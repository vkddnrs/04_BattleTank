// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	//ControlledTank = GetPawn();
	//AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if(!ensure(PlayerTank) || !ensure(AimingComponent)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if(AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();
	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if(InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if(!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->TankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}	
}

void ATankAIController::OnTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is died"), *GetPawn()->GetName())
	GetPawn()->DetachFromControllerPendingDestroy();
}


