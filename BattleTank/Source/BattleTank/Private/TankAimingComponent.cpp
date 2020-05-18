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
    UE_LOG(LogTemp, Warning, TEXT("time secs: %f vs last fired: %f"), GetWorld()->GetTimeSeconds(), LastFiredTime);
    if ((GetWorld()->GetTimeSeconds() - LastFiredTime) < ReloadTimeInSeconds)
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

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    FVector BarrelForwards = Barrel->GetForwardVector();
    return !BarrelForwards.Equals(AimDirection, MoveTolerance);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel && Turret)) { return; }

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
        MoveBarrelTowards();
        MoveTurretTowards();
    }
}

void UTankAimingComponent::MoveTurretTowards()
{
    // work out the difference between turret rotation and the aim direction
    FRotator TurretRotation = Turret->GetForwardVector().Rotation();
    FRotator AimRotation = AimDirection.Rotation();
    FRotator DeltaRotation = AimRotation - TurretRotation;

    Turret->RotateTurret(DeltaRotation.Yaw);
}

void UTankAimingComponent::MoveBarrelTowards()
{
    // work out the difference between the barrel rotation and the aim direction
    FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
    FRotator AimRotation = AimDirection.Rotation();
    FRotator DeltaRotation = AimRotation - BarrelRotation;

    // move the barrel the right amount this frame
    Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::Fire()
{
    if (FiringState != EFiringState::Reloading)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }

        LastFiredTime = GetWorld()->GetTimeSeconds();

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

