// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Handles by-wire movement of the tank
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

    public:
        UFUNCTION(BlueprintCallable, Category = Input)
            void InitialiseTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

        UFUNCTION(BlueprintCallable, Category = Input)
            void SetForwardIntent(float Throw);

        UFUNCTION(BlueprintCallable, Category = Input)
            void SetTurnRightIntent(float Throw);

    private:
        UTankTrack* LeftTrack = nullptr;
        UTankTrack* RightTrack = nullptr;
};

