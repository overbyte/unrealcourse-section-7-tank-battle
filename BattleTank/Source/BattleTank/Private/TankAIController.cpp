// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    auto ControlledTank = GetPawn();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (!ensure(PlayerTank && ControlledTank)) { return; }

    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);

    // aim at player
    UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    // fire
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        // Subscribe to Tank.OnDeath events
        PossessedTank->OnDestroyed.AddUniqueDynamic(this, &ATankAIController::OnTankDestruction);
    }
}

void ATankAIController::OnTankDestruction()
{
    if (!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}
