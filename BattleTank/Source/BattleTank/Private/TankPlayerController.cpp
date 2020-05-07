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

    AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair() const
{
    if (!GetControlledTank()) { return; }

    FVector OutHitLocation;
    if (GetSightRayHitLocation(OutHitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("hit location: %s"), *OutHitLocation.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
    // cast ray from camera through dot
    // if there's a collision and it's not a tank
    // update the hit location out param
    OutHitLocation = FVector(1.f);
    return true;
    // otherwise
    // return false
}
