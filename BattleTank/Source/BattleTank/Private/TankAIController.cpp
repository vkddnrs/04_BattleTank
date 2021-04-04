// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//if (GetPossessedTank())
	//	UE_LOG(LogTemp, Warning, TEXT("TankAIController posesses: %s"), *GetPossessedTank()->GetName())
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("TankAIController not posessing tank"))

	//ATank* Tank = GetPlayerTank();
	//if (Tank)
	//	Tank->AimAt(Tank->GetActorLocation());
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("TankAIController is not aimed"))
	
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO Move towards the player
	
	// Aim towards the player
	const auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{	
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}

//ATank* ATankAIController::GetPossessedTank() const
//{
//	return Cast<ATank>(GetPawn());
//}
//
//ATank* ATankAIController::GetPlayerTank() const
//{
//	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
//}
