// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    FindControlledTank();
    FindPlayerTank();
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!GetPlayerTank()) { return; }
    AimAtPlayerTank();
}

void ATankAIController::FindControlledTank() const
{
    const ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("No Controlled Tank Found"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank controlled by AI: %s"), *ControlledTank->GetName());
    }
}

void ATankAIController::FindPlayerTank() const
{
    const ATank* PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Error, TEXT("No Player Tank Found"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Found you, %s"), *PlayerTank->GetName());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimAtPlayerTank() const
{
    if (!GetPlayerTank()) { return; }
    if (!GetControlledTank()) { return; }
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

