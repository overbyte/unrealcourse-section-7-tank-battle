// Copyright 2020 Allandt Bik-Elliott


#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // change tick group so that the tick happens after the physics calculation
    PrimaryActorTick.TickGroup = TG_PostPhysics;

    MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
    SetRootComponent(MassWheelConstraint);

    Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
    Axel->SetupAttachment(MassWheelConstraint);

    Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
    Wheel->SetupAttachment(Axel);

    WheelAxelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelAxelConstraint"));
    WheelAxelConstraint->SetupAttachment(Axel);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

    SetupConstraint();

    Wheel->SetNotifyRigidBodyCollision(true);
    // register delegate for oncomponenthit events
    Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
}

void ASprungWheel::SetupConstraint()
{
    if (!GetAttachParentActor()) { return; }
    UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
    if (!BodyRoot) { return; }

    MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axel, NAME_None);
    WheelAxelConstraint->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // double check tick group
    if (GetWorld()->TickGroup == TG_PostPhysics)
    {
        // reset current force magnitude post physics
        CurrentForceMagnitude = 0.f;
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("Tick isn't happening at the right time"));
    }
}

void ASprungWheel::AddDrivingForce(float Magnitude)
{
    CurrentForceMagnitude += Magnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    ApplyForce();
}

void ASprungWheel::ApplyForce()
{
    Wheel->AddForce(Axel->GetForwardVector() * CurrentForceMagnitude);
}
