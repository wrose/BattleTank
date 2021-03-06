// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 4000.f; // Sane default

private:
    virtual void BeginPlay() override;

    void Tick(float DeltaTime);

	UTankAimingComponent* TankAimingComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;

    UFUNCTION()
    void OnTankDeath();
};
