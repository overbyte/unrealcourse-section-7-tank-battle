// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    ATank* ControlledTank = Cast<ATank>(GetPawn());
    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!PlayerTank || !ControlledTank) { return; }

    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);
    // aim at player
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    // fire
    ControlledTank->Fire();
}

