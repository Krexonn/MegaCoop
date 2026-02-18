// Copyright Krexonn


#include "Actors/Player/MC_SpiningAxe.h"


// Sets default values
AMC_SpiningAxe::AMC_SpiningAxe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMC_SpiningAxe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMC_SpiningAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

