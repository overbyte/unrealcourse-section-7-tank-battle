// Copyright 2020 Allandt Bik-Elliott

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, Category = "Setup")
        TSubclassOf<AActor> SpawnClass;

private:
    void SetupConstraint();
};
