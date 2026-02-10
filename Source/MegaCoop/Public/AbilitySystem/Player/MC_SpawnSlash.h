// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Actors/Player/MC_SlashEffectActor.h"
#include "MC_SpawnSlash.generated.h"


UCLASS()
class MEGACOOP_API UMC_SpawnSlash : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UMC_SpawnSlash();

	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Abilities")
	void SpawnSlashActor();
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MegaCoop|Config")
	int32 SlashCount = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MegaCoop|Config")
	float SlashSizeScale = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Config")
	TSubclassOf<AMC_SlashEffectActor> SlashActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Config")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
};
