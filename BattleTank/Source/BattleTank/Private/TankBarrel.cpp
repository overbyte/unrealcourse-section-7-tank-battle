// Copyright 2020 Allandt Bik-Elliott


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    float DeltaElevation = RelativeSpeed * MaxRotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = GetRelativeRotation().Pitch + DeltaElevation;
    float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}


