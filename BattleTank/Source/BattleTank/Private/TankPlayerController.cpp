// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"

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
    // get crosshair (dot) position
    // get viewport size
    int32 OutViewportSizeX;
    int32 OutViewportSizeY;
    GetViewportSize(OutViewportSizeX, OutViewportSizeY);

    FVector2D ScreenLocation(
            OutViewportSizeX * CrosshairXLocation,
            OutViewportSizeY * CrosshairYLocation
        );

    FVector OutLookDirection;
    if (GetLookDirection(ScreenLocation, OutLookDirection))
    {
        // cast ray from camera through crosshair to maximum range
        GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
    }
    // if there's a collision and it's not a tank
    // update the hit location out param
    return true;
    // otherwise
    // return false
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

FVector ATankPlayerController::GetViewPointPos() const
{
    // out params
    FVector OutViewPointPosition;
    FRotator OutViewPointRotation;

    GetPlayerViewPoint(
        OutViewPointPosition,
        OutViewPointRotation
    );

    return OutViewPointPosition;
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

    if (GetWorld()->LineTraceSingleByChannel(
            OutHitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility,
            CollisionParams,
            FCollisionResponseParams(ECollisionResponse::ECR_Block)
        )
    )
    {
        OutHitLocation = OutHitResult.Location;
        return true;
    }
    return false;
}
