// Copyright 2020 Allandt Bik-Elliott

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();

    // ensure that tank can't fire until at least one reload
    LastFiredTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent ( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
    if (AmmoCount <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((GetWorld()->GetTimeSeconds() - LastFiredTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    FVector BarrelForwards = Barrel->GetForwardVector();
    return !BarrelForwards.Equals(AimDirection, MoveTolerance);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Turret)) { return; }
    if (!ensure(Barrel)) { return; }

    FVector OutLaunchVelocity(0);
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        Barrel->GetSocketLocation(FName("Projectile")),
        HitLocation,
        LaunchSpeed,
        false,
        0.f,
        0.f,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );

    float TimeInSeconds = GetWorld()->GetTimeSeconds();
    if (bHaveAimSolution)
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveTurretTowards();
    }
}

void UTankAimingComponent::MoveTurretTowards()
{
    // work out the difference between turret rotation and the aim direction
    FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
    FRotator AimRotation = AimDirection.Rotation();
    FRotator DeltaRotation = AimRotation - BarrelRotation;

    Barrel->Elevate(DeltaRotation.Pitch);

    // find the shortest route
    if (FMath::Abs(DeltaRotation.Yaw) < 180)
    {
        Turret->RotateTurret(DeltaRotation.Yaw);
    }
    else
    {
        Turret->RotateTurret(-DeltaRotation.Yaw);
    }
}

void UTankAimingComponent::Fire()
{
    if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }

        // update game state
        LastFiredTime = GetWorld()->GetTimeSeconds();
        --AmmoCount;

        FVector ProjectileSocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
        FRotator BarrelRotation = Barrel->GetSocketRotation(FName("Projectile"));

        AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            ProjectileSocketLocation,
            BarrelRotation
        );

        Projectile->Launch(LaunchSpeed);

    }
}

int32 UTankAimingComponent::GetAmmoCount() const
{
    return AmmoCount;
}

