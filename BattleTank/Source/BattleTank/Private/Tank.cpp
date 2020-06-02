// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent()
{
    // cast int32 to float and get health expressed from 0-1
    return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

    CurrentHealth -= DamageToApply;
    UE_LOG(LogTemp, Warning, TEXT("%s lost %i health. remaining: %i"), *GetName(), DamageToApply, CurrentHealth);

    if (CurrentHealth <= 0)
    {
        OnDestroyed.Broadcast();
    }

    return DamageToApply;
}
