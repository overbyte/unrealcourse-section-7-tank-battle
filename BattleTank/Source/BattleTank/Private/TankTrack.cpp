// Copyright 2020 Allandt Bik-Elliott


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();

    // register delegate for oncomponenthit events
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent ( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector RightVelocity = GetRightVector();
    FVector ForwardVelocity = GetComponentVelocity();
    float SlippageSpeed = FVector::DotProduct(RightVelocity, ForwardVelocity); 
    // work out the required acceleration in m/s/s to correct this slippage
    FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * RightVelocity;
    // calculate and apply sideways friction (opposite acceleration) for F = ma
    // note: there are two tracks so divide by 2
    UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
    TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("track is on floor"));
}

void UTankTrack::SetThrottle(float Throttle)
{
    // TODO clamp throttle to avoid sensitivity adding speed to the tank

    FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForceNewtons;
    FVector ForceLocation = GetComponentLocation();
    UPrimitiveComponent *TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

