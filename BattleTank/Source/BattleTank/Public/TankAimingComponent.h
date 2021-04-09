// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankTurret;
class UTankBarrel;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//************************************************************

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	
private:
	UTankBarrel* Barrel = nullptr; // ����� �����
	UTankTurret* Turret = nullptr; // �����
	void MoveBarrelTowards(FVector AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringStatus = EFiringState::Aiming;
	
};
