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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "MegaCoop|Shield")
	AActor* OwnerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Shield")
	float CurrentAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Shield")
	float RotationSpeed = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Shield")
	float Radius = 150.0f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Shield")
	float VerticalOffset = 50.0f; 
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Gas")
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
