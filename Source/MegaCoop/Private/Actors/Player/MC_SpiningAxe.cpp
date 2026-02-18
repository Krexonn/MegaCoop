// Copyright Krexonn


#include "Actors/Player/MC_SpiningAxe.h"

#include "Utils/MC_BlueprintLibrary.h"


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

void AMC_SpiningAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMC_SpiningAxe::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bIsEnemy = OtherActor->ActorHasTag(FName("Enemy"));
	if (bIsEnemy)
	{
		UMC_BlueprintLibrary::ApplyHybridDamage(
			this,
			OtherActor,
			ProjectileDamage,
			DamageEffectSpecHandle);
	}
	
}

// Called every frame


