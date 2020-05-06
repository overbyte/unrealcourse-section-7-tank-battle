// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    FindControlledTank();
    FindPlayerTank();
}

void ATankAIController::FindControlledTank()
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

void ATankAIController::FindPlayerTank()
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

ATank* ATankAIController::GetControlledTank()
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


