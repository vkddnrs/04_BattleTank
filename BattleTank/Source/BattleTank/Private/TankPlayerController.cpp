// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());	
}

void ATankPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay"))

	if(GetControlledTank())
		UE_LOG(LogTemp, Warning, TEXT("ControlledTank posesses: %s"), *GetControlledTank()->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("ControlledTank not posessing tank"))

}
