// Copyright 2020 Allandt Bik-Elliott


#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h" 


// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

    // start spawning actor but defer it
    auto ActorToSpawn = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
    if (!ActorToSpawn) { return; }
    // attach to world (not local)
    ActorToSpawn->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
    // finish spawning actor
    UGameplayStatics::FinishSpawningActor(ActorToSpawn, GetComponentTransform());
}

