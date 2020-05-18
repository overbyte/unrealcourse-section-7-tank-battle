// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Note: this is a forward declaration which will be filled in properly in the
// actual class declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

    public:	
        UFUNCTION(BlueprintCallable, Category = "Setup")
            void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

        void AimAt(FVector HitLocation);

        UFUNCTION(BlueprintCallable, Category = "Firing")
            void Fire();

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
            float LaunchSpeed = 4000.f; // starting number 1000 m/s

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
            float ReloadTimeInSeconds = 3.f;

    protected:
        UPROPERTY(BlueprintReadOnly, Category = "Firing")
            EFiringState FiringState = EFiringState::Locked;

    private:
        UTankAimingComponent();

        UPROPERTY(EditDefaultsOnly, Category = "Setup")
            TSubclassOf<AProjectile> ProjectileBlueprint;

        UTankBarrel* Barrel = nullptr;
        UTankTurret* Turret = nullptr;
        double LastFiredTime = 0;

        void MoveBarrelTowards(FVector AimDirection);
        void MoveTurretTowards(FVector AimDirection);
};
