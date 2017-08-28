// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
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
	virtual void BeginPlay() override;

private:
    void Tick(float DeltaTime);

    void AimTowardsPlayer(ATank *ControlledTank, ATank *PlayerTank);

	UPROPERTY(EditDefaultsOnly)
    float AcceptanceRadius = 30.f; // Sane default?
};
