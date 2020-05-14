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


