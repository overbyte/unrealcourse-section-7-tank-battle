// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankBarrel;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

    public:
        // Sets default values for this pawn's properties
        ATank();
        virtual void BeginPlay() override;

        UFUNCTION(BlueprintCallable, Category = "Firing")
            void Fire();

    private:
        UPROPERTY(EditDefaultsOnly, Category = "Setup")
            TSubclassOf<AProjectile> ProjectileBlueprint;

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
            float LaunchSpeed = 4000.f; // starting number 1000 m/s

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
            float ReloadTimeInSeconds = 3.f;

        double LastFiredTime = 0;
        // TODO remove barrel
        UTankBarrel *Barrel = nullptr;
};
