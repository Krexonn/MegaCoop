// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MC_ActivateShield.generated.h"

/**
 * 
 */
UCLASS()
class MEGACOOP_API UMC_ActivateShield : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Shield System")
	TSubclassOf<class AMC_OrbitalShield> ShieldClass;
	
	UPROPERTY() 
	TArray<AMC_OrbitalShield*> ActiveShields;
};
