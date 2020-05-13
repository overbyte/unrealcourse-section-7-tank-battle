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

    // NOTE: We are setting this in the constructor so don't need to protect pointer
    AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    AimingComponent->SetBarrelReference(BarrelToSet);
    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
    AimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
    if (!Barrel) { return; }

    FVector ProjectileSocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator BarrelRotation = Barrel->GetSocketRotation(FName("Projectile"));

    UE_LOG(LogTemp, Warning, TEXT("loc: %s, rot: %s"), *ProjectileSocketLocation.ToString(), *BarrelRotation.ToString());

    GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        ProjectileSocketLocation,
        BarrelRotation
    );

    float TimeInSeconds = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f SHOOT ALL THE THINGS"), TimeInSeconds);
}

void ATank::AimAt(FVector HitLocation) const
{
    AimingComponent->AimAt(HitLocation, LaunchSpeed);
}
