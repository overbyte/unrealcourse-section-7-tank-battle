// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	
	public:
        virtual void Tick(float DeltaSeconds) override;
        virtual void BeginPlay() override;

        UPROPERTY(EditDefaultsOnly)
            float CrosshairXLocation = 0.5f;

        UPROPERTY(EditDefaultsOnly)
            float CrosshairYLocation = 0.33333f;

        UPROPERTY(EditDefaultsOnly)
            float ProjectileRange = 1000000.f;

    protected:
        UFUNCTION(BlueprintCallable, Category = "Setup")
            ATank* GetControlledTank() const;

    private:
        void AimTowardCrosshair() const;
        bool GetSightRayHitLocation(FVector &OutHitLocation) const;
        bool GetLookDirection(const FVector2D &ScreenLocation, FVector &OutWorldDirection) const;
        bool GetLookVectorHitLocation(const FVector &LookDirection, FVector &OutHitLocation) const;
};
