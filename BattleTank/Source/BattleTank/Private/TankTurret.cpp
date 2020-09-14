// Copyright 2020 Allandt Bik-Elliott


#include "TankTurret.h"


void UTankTurret::RotateTurret(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    float DeltaRotation = RelativeSpeed * MaxRotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float NewRotation = GetRelativeRotation().Yaw + DeltaRotation;

    SetRelativeRotation(FRotator(0, NewRotation, 0));
}


