// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "MC_OrbitalShield.generated.h"

UCLASS()
class MEGACOOP_API AMC_OrbitalShield : public AActor
{
	GENERATED_BODY()

public:
	AMC_OrbitalShield();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	AActor* OwnerCharacter;
	
	float CurrentAngle; 
	float RotationSpeed = 180.0f;
	float Radius = 150.0f;     
	float VerticalOffset = 50.0f; 
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComp;

	// Düşmana çarpma eventi
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);
	
};
