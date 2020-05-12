// Copyright 2020 Allandt Bik-Elliott

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::TickComponent ( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }

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
        UE_LOG(LogTemp, Warning, TEXT("%f aim solution found"), TimeInSeconds);
        FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%f no aim solution"), TimeInSeconds);
    }

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // work out the difference between the barrel rotation 
    // and the aim direction
    FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
    FRotator AimRotation = AimDirection.Rotation();
    FRotator DeltaRotation = AimRotation - BarrelRotation;
    // move the barrel the right amount this frame
    Barrel->Elevate(DeltaRotation.Pitch);
}
