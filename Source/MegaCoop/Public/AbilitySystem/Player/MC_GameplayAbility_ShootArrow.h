// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MC_GameplayAbility_ShootArrow.generated.h"

class AMC_Projectile_Arrow;

UCLASS()
class MEGACOOP_API UMC_GameplayAbility_ShootArrow : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UMC_GameplayAbility_ShootArrow();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// Oku fırlatma işlemini yapacak fonksiyon
	UFUNCTION()
	void FireArrow();

	// Atış Sıklığı (Saniye cinsinden, örn: her 1 saniyede 1 ok)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow")
	float FireRate;

	// Hedef menzili
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow")
	float TargetingRadius;

	// Atılacak mermi sınıfı
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow")
	TSubclassOf<AMC_Projectile_Arrow> ProjectileClass;

	// Çarpışma taramasında kullanılacak obje tipleri (Örn: Pawn, Enemy katmanları)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arrow")
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectTypes;

private:
	FTimerHandle FireTimerHandle;
};
