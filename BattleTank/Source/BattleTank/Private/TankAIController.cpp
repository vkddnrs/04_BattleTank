// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetPosessedTank())
		UE_LOG(LogTemp, Warning, TEXT("TankAIController posesses: %s"), *GetPosessedTank()->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not posessing tank"))

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
	ATank* AimTank = GetPlayerTank();
	if (AimTank)
		GetPosessedTank()->AimAt(AimTank->GetActorLocation());
	else
		UE_LOG(LogTemp, Warning, TEXT("TankAIController is not aimed"))

	// Fire if ready
}

ATank* ATankAIController::GetPosessedTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
