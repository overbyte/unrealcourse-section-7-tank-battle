// Copyright 2020 Allandt Bik-Elliott


#include "TankTrack.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
    float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
    DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
    float ForceApplied = CurrentThrottle * MaxDrivingForceNewtons;
    // get wheel array
    TArray<ASprungWheel*> Wheels = GetWheels();
    float WheelForceMagnitude = ForceApplied / Wheels.Num();
    // loop through array
    for (ASprungWheel* Wheel : Wheels)
    {
        // add force per wheel
        Wheel->AddDrivingForce(WheelForceMagnitude);
    }
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
    TArray<USceneComponent*> OutChildren;
    GetChildrenComponents(true, OutChildren);

    TArray<ASprungWheel*> Wheels;
    for (USceneComponent* Child : OutChildren)
    {
        auto SpawnPointChild = Cast<USpawnPoint>(Child);
        if (!SpawnPointChild) { continue; } // if the cast fails, go to next loop

        auto SprungWheel = Cast<ASprungWheel>(SpawnPointChild->GetSpawnedActor());
        if (!SprungWheel) { continue; }

        Wheels.Emplace(SprungWheel);
    }
    return Wheels;
}
