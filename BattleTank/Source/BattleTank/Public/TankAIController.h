// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
    public:
        ATank* GetControlledTank() const;
        ATank* GetPlayerTank() const;
        virtual void Tick(float DeltaSeconds) override;
	
    protected:
        virtual void BeginPlay() override;
	
    private:
        void FindControlledTank() const;
        void FindPlayerTank() const;
        void AimAtPlayerTank() const;
};
