// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()

    ATankPlayerController();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    ATank *GetControlledTank() const;


    // Start the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world
    void AimTowardsCrosshair();

protected:
    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;

    bool GetSightRayHitLocation(FVector &HitLocation) const;

    FVector GetLineReachStart();

    FVector GetLineReachEnd();

//    bool GetSightRayHitLocation(FVector &HitLocation);
};
