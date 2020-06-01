// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    OutOfAmmo,
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

        UFUNCTION(BlueprintCallable, Category = "Firing")
            void Fire();

        UFUNCTION(BlueprintCallable, Category = "Firing")
            int32 GetAmmoCount() const;

        void AimAt(FVector HitLocation);
        EFiringState GetFiringState() const;

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
            float LaunchSpeed = 4000.f; // starting number 1000 m/s

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
            float ReloadTimeInSeconds = 3.f;

    protected:
        UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Firing")
            EFiringState FiringState = EFiringState::Reloading;

        UPROPERTY(VisibleAnywhere, Category = "Firing")
            int32 AmmoCount = 10;

        // originally this was set as private + EditDefaultsOnly and the
        // BP_Projectile was added in the Tank blueprint but a bug in ue causes
        // this to become unset when starting from the main menu. The fix is to
        // use blueprintreadwrite and set the BP_Projectile in the blueprint
        // construction script: https://www.udemy.com/course/unrealcourse/learn/lecture/5519298#questions/10844328
        // TODO would be good to go back to the original architecture but not
        // necessary
        UPROPERTY(BlueprintReadWrite, Category = "Setup")
            TSubclassOf<AProjectile> ProjectileBlueprint;

    private:
        UTankAimingComponent();
        virtual void BeginPlay() override;
        virtual void TickComponent ( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;
        void MoveTurretTowards();
        bool IsBarrelMoving();

        UTankBarrel* Barrel = nullptr;
        UTankTurret* Turret = nullptr;
        double LastFiredTime = 0;
        FVector AimDirection = FVector(0);
        float MoveTolerance = 0.01f;
};
