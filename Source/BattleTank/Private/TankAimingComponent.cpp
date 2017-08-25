// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/StaticMesh.h"
#include <EngineClasses.h>
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

    if (!Barrel) { return; }

    auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FVector OutLaunchVelocity;

    // Calculate the OutLaunchVelocity
    auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                this,
                OutLaunchVelocity,
                StartLocation,
                HitLocation,
                LaunchSpeed,
                false,
                0,
                0,
                ESuggestProjVelocityTraceOption::DoNotTrace
        );

    if (bHaveAimSolution) {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time);
    } else {
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
    }

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet) {
    Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
}