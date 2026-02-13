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
	
public:
	
	UPROPERTY()
	class UMC_AttributeSet* AttributeSet;
	
	FActiveGameplayEffectHandle ShieldEffectHandle;
	
	void ApplyShieldEffect();
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MegaCoop|Shield")
	TSubclassOf<UGameplayEffect> ShieldEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Shield")
	TSubclassOf<class AMC_OrbitalShield> ShieldClass;
	
	UPROPERTY() 
	TArray<AMC_OrbitalShield*> ActiveShields;
	
	FTimerHandle TimerHandle_ShieldRegen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Shield")
	float ShieldCheckInterval = 3.0f;
	
	
	
	UFUNCTION() 
	void CheckAndSpawnShield();
	
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Shield")
	void GetTimerEvent();
	
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Shield")
	void SpawnSingleShield();
	
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Shield")
	void CheckStackCount(FActiveGameplayEffectHandle ActiveHandle) const;
	
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Shield")
	void SetCurrentAngel(int LastIndex);
};
