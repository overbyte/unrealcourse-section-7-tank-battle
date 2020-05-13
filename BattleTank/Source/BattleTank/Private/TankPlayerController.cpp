// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("No possessed Tank was found"));
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
        GetControlledTank()->AimAt(OutHitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
    // get crosshair (dot) position
    // get viewport size
    int32 OutViewportSizeX;
    int32 OutViewportSizeY;
    GetViewportSize(OutViewportSizeX, OutViewportSizeY);

    FVector2D ScreenLocation
    (
        OutViewportSizeX * CrosshairXLocation,
        OutViewportSizeY * CrosshairYLocation
    );

    FVector OutLookDirection;
    if (GetLookDirection(ScreenLocation, OutLookDirection))
    {
        // cast ray from camera through crosshair to maximum range
        return GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
    }
    return false;
}

// "de-project" the screen position of the crosshair to a world pos
bool ATankPlayerController::GetLookDirection(const FVector2D &ScreenLocation, FVector &OutWorldDirection) const
{
    FVector OutCameraWorldLocation;
    return DeprojectScreenPositionToWorld(
            ScreenLocation.X,
            ScreenLocation.Y,
            OutCameraWorldLocation,
            OutWorldDirection
        );
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector &LookDirection, FVector &OutHitLocation) const
{
    FCollisionQueryParams CollisionParams(
        FName(TEXT("")),
        false,
        GetPawn()
    );

    FHitResult OutHitResult;

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + LookDirection * ProjectileRange;

    bool bHasAimSolution = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility/*,
        CollisionParams,
        FCollisionResponseParams(ECollisionResponse::ECR_Block*/
    );

    if (bHasAimSolution)
    {
        OutHitLocation = OutHitResult.Location;
        return true;
    }

    OutHitLocation = FVector(0.f);
    return false;
}
