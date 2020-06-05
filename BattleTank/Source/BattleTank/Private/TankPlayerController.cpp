// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!GetPawn()) { return; }

    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AimTowardCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        // Subscribe to Tank.OnDeath events
        PossessedTank->OnDestroyed.AddUniqueDynamic(this, &ATankPlayerController::OnTankDestruction);
    }
}

void ATankPlayerController::OnTankDestruction()
{
    if (!GetPawn()) { return; }
    StartSpectatingOnly();
}

void ATankPlayerController::AimTowardCrosshair() const
{
    if (!ensure(GetPawn())) { return; }
    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; } 
    FVector OutHitLocation;
    if (GetSightRayHitLocation(OutHitLocation))
    {
        AimingComponent->AimAt(OutHitLocation);
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
    FHitResult OutHitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + LookDirection * ProjectileRange;

    bool bHasAimSolution = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Camera
    );

    if (bHasAimSolution)
    {
        OutHitLocation = OutHitResult.Location;
        return true;
    }

    OutHitLocation = FVector(0.f);
    return false;
}
