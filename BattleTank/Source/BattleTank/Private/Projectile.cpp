// Copyright 2020 Allandt Bik-Elliott


#include "Projectile.h"
#include "Kismet/GameplayStatics.h" 


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // default add move component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false;

    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(true);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->bAutoActivate = false;
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

    // register delegate for oncomponenthit events
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Launch(float AtSpeed)
{
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * AtSpeed);
    ProjectileMovement->Activate();
}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();

    // remove visible shell from world while leaving particles
    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();

    // apply damage
    UGameplayStatics::ApplyRadialDamage(
        this, 
        ProjectileDamage,
        GetActorLocation(),
        ExplosionForce->Radius,
        UDamageType::StaticClass(),
        TArray<AActor*>() // empty set - damage all actors
    );

    // set a timer to destroy projectile completely
    FTimerHandle OutTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(OutTimerHandle, this, &AProjectile::RetireProjectile, TimeToDestroy, false);
}

void AProjectile::RetireProjectile()
{
    Destroy();
}
