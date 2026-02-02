// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MC_HitReact.generated.h"


UCLASS()
class MEGACOOP_API UMC_HitReact : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "Crash|Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "Crash|Abilities")
	FVector ToInstagtor;
};
