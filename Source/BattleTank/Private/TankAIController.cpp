// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


ATankAIController::ATankAIController() {
    PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if (!ensure(PlayerTank && ControlledTank)) { return; }

    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

    // Aim towards player
    TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

    // Fire when ready
    if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
    TankAimingComponent->Fire();
}

void ATankAIController::SetPawn(APawn* InPawn) {
    Super::SetPawn(InPawn);

    if (InPawn) {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath() {
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *Name)

    auto ControlledTank = GetPawn();
    ControlledTank->DetachFromControllerPendingDestroy();
}