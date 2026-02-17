// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "MC_SlashEffectActor.generated.h"

class UBoxComponent;    
class UNiagaraComponent;  
class URotatingMovementComponent; 
class USceneComponent;

UCLASS()
class MEGACOOP_API AMC_SlashEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AMC_SlashEffectActor();

protected:
	virtual void BeginPlay() override;

public:    
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	float ProjectileDamage = 10.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	TObjectPtr<UBoxComponent> CollisionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	TObjectPtr<UNiagaraComponent> NiagaraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	TObjectPtr<URotatingMovementComponent> RotationComp;
	
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
	TSet<AActor*> HitActors;
	
	void SetDamageSpec(FGameplayEffectSpecHandle Handle);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
