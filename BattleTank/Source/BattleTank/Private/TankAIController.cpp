// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	if (GetPosessedTank())
		UE_LOG(LogTemp, Warning, TEXT("TankAIController posesses: %s"), *GetPosessedTank()->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not posessing tank"))
	
}

ATank* ATankAIController::GetPosessedTank() const
{
	return Cast<ATank>(GetPawn());
}
