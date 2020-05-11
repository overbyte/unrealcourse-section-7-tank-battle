// Copyright 2020 Allandt Bik-Elliott

#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) const
{
    if (!Barrel) { return; }

    FVector OutLaunchVelocity(0);
    if (
        UGameplayStatics::SuggestProjectileVelocity
        (
            this,
            OutLaunchVelocity,
            Barrel->GetSocketLocation(FName("Projectile")),
            HitLocation,
            LaunchSpeed,
            false,
            0.f,
            0.f,
            ESuggestProjVelocityTraceOption::TraceFullPath
        )
    )
    {
        FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
        UE_LOG(LogTemp, Warning, TEXT("Aiming At %s"), *AimDirection.ToString());
    }

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // work out the difference between the barrel rotation 
    // and the aim direction
    FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
    FRotator AimRotation = AimDirection.Rotation();
    FRotator DeltaRotation = AimRotation - BarrelRotation;
    UE_LOG(LogTemp, Warning, TEXT("Aim rotation: %s"), *DeltaRotation.ToString());
    // move the barrel the right amount this frame
}
