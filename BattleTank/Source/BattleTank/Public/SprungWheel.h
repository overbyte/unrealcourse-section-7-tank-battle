// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;
class ASprungWheel;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
        
    public:	
        // Called every frame
        virtual void Tick(float DeltaTime) override;
        void AddDrivingForce(float Magnitude);

    protected:
        // Called when the game starts or when spawned
        virtual void BeginPlay() override;

    private:
        // Sets default values for this actor's properties
        ASprungWheel();

        UFUNCTION()
            void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

        void SetupConstraint();
        TArray<ASprungWheel> GetWheels() const;
        void ApplyForce();

        UPROPERTY(VisibleAnywhere, Category = "Components")
            USphereComponent* Wheel = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Components")
            USphereComponent* Axel = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Components")
            UPhysicsConstraintComponent* WheelAxelConstraint = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Components")
            UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

        float AxelRadius = 10.f;
        float WheelRadius = 100.f;
        float CurrentForceMagnitude = 0.f;
};
