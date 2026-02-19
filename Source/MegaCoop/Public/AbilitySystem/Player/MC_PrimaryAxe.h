// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Actors/Player/MC_SpiningAxe.h"
#include "MC_PrimaryAxe.generated.h"


UCLASS()
class MEGACOOP_API UMC_PrimaryAxe : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Abilities")
	void SpawnSpiningAxe();
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Config")
	TSubclassOf<AMC_SpiningAxe> SpiningAxeClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Config")
	float SpreadDistance = 150.f;
private:
	
	FTransform CalculateSpawnTransform(int32 Index);
	
	int32 GetProjectileCount();
};