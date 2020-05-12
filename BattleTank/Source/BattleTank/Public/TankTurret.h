// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Holds properties and methods for the Tank Turret
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void RotateTurret(float RelativeSpeed);

private:
    UPROPERTY(EditAnywhere, Category = Setup)
        float MaxRotationDegreesPerSecond = 25.f;
};
