// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Holds properties and methods for the Tank Track
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

    public:
        UFUNCTION(BlueprintCallable, Category = "Input")
            void SetThrottle(float Throttle);
        
        UPROPERTY(EditDefaultsOnly, Category = "Input")
            float MaxDrivingForceNewtons = 40000000.f; // assume 40 tonne tank and 1g acceleration

    private:
        UTankTrack();

        UFUNCTION()
            void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

        virtual void BeginPlay() override;
        void ApplySidewaysForce();
        void DriveTrack();

        float CurrentThrottle = 0.f;
};
