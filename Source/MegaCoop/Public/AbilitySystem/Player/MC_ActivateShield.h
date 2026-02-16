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
	
	FActiveGameplayEffectHandle ShieldActiveEffectHandle;

	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MegaCoop|Shield")
	TSubclassOf<UGameplayEffect> ShieldStackEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MegaCoop|Shield")
	TSubclassOf<class AMC_OrbitalShield> ShieldClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "MegaCoop|Shield") 
	TArray<AMC_OrbitalShield*> ActiveShields;
	
	FTimerHandle TimerHandle_ShieldRegen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Shield")
	float ShieldCheckInterval = 3.0f;
	
	
	
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|Shield")
	void GetTimerEvent();
	
	UFUNCTION() 
	void CheckAndSpawnShield();
	
	UFUNCTION()
	void SpawnSingleShield();
	
	UFUNCTION()
	int CheckStackCount(FActiveGameplayEffectHandle ActiveHandle) const;
	
	UFUNCTION()
	void SetCurrentAngle(int LastIndex);
	
	UFUNCTION()
	void ApplyShieldEffect();
};
