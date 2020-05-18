// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
{
    if (!ensure(Barrel)) { return; }

    bool bIsReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSeconds;

    if (bIsReloaded)
    {
        LastFiredTime = FPlatformTime::Seconds();

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

void ATank::AimAt(FVector HitLocation) const
{
    if (!ensure(AimingComponent)) { return; }
    AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

