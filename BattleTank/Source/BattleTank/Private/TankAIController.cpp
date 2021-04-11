// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	//ControlledTank = GetPawn();
	//AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if(!ensure(PlayerTank) || !ensure(AimComponent)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	AimComponent->AimAt(PlayerTank->GetActorLocation());
	AimComponent->Fire();
	
}


