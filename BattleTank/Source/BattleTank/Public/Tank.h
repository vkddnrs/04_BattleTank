// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
 //************************************************

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	// Return current health as a percentage of starting health, between 0 and 1 
	UFUNCTION(BlueprintPure, Category = "Health")		
		float GetHealthPercent() const;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float Health = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHealth = Health;
};
