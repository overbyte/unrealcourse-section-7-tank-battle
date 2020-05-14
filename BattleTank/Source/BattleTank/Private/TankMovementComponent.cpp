// Copyright 2020 Allandt Bik-Elliott


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitialiseTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::SetForwardIntent(float Throw)
{
    if (!LeftTrack|| !RightTrack) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::SetTurnRightIntent(float Throw)
{
    if (!LeftTrack|| !RightTrack) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    auto TankName = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s moving at %s"), *TankName, *MoveVelocity.ToString());
}
