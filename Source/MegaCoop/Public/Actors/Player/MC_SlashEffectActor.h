// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "MC_SlashEffectActor.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class MEGACOOP_API AMC_SlashEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMC_SlashEffectActor();

protected:
	virtual void BeginPlay() override;

public:    
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	TObjectPtr<USphereComponent> CollisionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	TObjectPtr<UNiagaraComponent> NiagaraComp;

	
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
	TSet<AActor*> HitActors;
	
	void SetDamageSpec(FGameplayEffectSpecHandle Handle);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
