// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Note: this is a forward declaration which will be filled in properly in the
// actual class declaration
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    virtual void TickComponent ( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction ) override;

    void AimAt(FVector HitLocation, float LaunchSpeed);
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    void SetTurretReference(UTankTurret* TurretToSet);

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    void MoveBarrelTowards(FVector AimDirection);
    void MoveTurretTowards(FVector AimDirection);
};
