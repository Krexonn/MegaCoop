// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_SpiningAxe.generated.h"

UCLASS()
class MEGACOOP_API AMC_SpiningAxe : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMC_SpiningAxe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
