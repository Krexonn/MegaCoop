// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "MC_SpiningAxe.generated.h"

UCLASS()
class MEGACOOP_API AMC_SpiningAxe : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMC_SpiningAxe();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MegaCoop")
	float ProjectileDamage = 10.f;
	
	UPROPERTY()
	TSet<AActor*> HitActors;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MegaCoop|Damage")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MegaCoop|Damage")
	float LifeTime = 1.f;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop|Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MegaCoop|Movement")
	class URotatingMovementComponent* RotatingMovementComponent;


};
