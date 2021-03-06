// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Holds properties and methods for the Tank Barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    //-1 max downward movement, +1 max upward movement
    void Elevate(float RelativeSpeed);
	
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
        float MaxRotationDegreesPerSecond = 10.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
        float MaxElevationDegrees = 60.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
        float MinElevationDegrees = 0.f;
	
};
