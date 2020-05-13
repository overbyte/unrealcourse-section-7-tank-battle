// Copyright 2020 Allandt Bik-Elliott


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{


    // TODO clamp throttle to avoid sensitivity adding speed to the tank

    FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForceNewtons;
    FVector ForceLocation = GetComponentLocation();
    UPrimitiveComponent *TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    UE_LOG(LogTemp, Warning, TEXT("%s Set throttle %f at loc %s"), *GetName(), Throttle, *ForceLocation.ToString());
}
