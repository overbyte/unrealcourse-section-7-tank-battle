// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("No possessed Tank was found"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("controlled tank: %s"), *ControlledTank->GetName());
    }
}


void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


