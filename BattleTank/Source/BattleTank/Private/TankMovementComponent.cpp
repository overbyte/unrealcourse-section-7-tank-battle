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
    if (!ensure(LeftTrack && RightTrack)) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::SetTurnRightIntent(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    FVector ForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

    // convert velocity into a unit vector (total of 1)
    FVector ForwardIntent = MoveVelocity.GetSafeNormal();

    // get the dot product (https://en.wikipedia.org/wiki/Dot_product)
    float DotProduct = FVector::DotProduct(ForwardDirection, ForwardIntent);
    SetForwardIntent(DotProduct);

    float CrossProduct = FVector::CrossProduct(ForwardDirection, ForwardIntent).Z;
    SetTurnRightIntent(CrossProduct);
}
