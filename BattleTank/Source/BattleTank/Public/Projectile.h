// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void Launch(float AtSpeed);

private:
    UProjectileMovementComponent *ProjectileMovement = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
        UStaticMeshComponent *CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
        UParticleSystemComponent *LaunchBlast = nullptr;
	
};
