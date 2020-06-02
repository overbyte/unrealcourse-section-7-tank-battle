// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

    protected:
        // how close the AI tank will get before it stops moving
        UPROPERTY(EditDefaultsOnly, Category = "Setup")
            float AcceptanceRadius = 10000.f;

    private:
        virtual void BeginPlay() override;
        virtual void Tick(float DeltaSeconds) override;
        virtual void SetPawn(APawn* InPawn) override;

        UFUNCTION()
            void OnTankDestruction();
};
