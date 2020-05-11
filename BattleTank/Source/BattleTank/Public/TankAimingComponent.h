// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Note: this is a forward declaration which will be filled in properly in the
// actual class declaration
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void AimAt(FVector HitLocation, float LaunchSpeed) const;
    void SetBarrelReference(UTankBarrel* BarrelToSet);

private:
    UTankBarrel* Barrel = nullptr;
    void MoveBarrelTowards(FVector AimDirection);
};
