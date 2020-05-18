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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

    public:	
        UFUNCTION(BlueprintCallable, Category = "Setup")
            void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

        void AimAt(FVector HitLocation, float LaunchSpeed);

    protected:
        UPROPERTY(BlueprintReadOnly, Category = "Firing")
            EFiringState FiringState = EFiringState::Locked;

    private:
        UTankAimingComponent();

        UTankBarrel* Barrel = nullptr;
        UTankTurret* Turret = nullptr;

        void MoveBarrelTowards(FVector AimDirection);
        void MoveTurretTowards(FVector AimDirection);
};
