// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_Projectile_Arrow.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class MEGACOOP_API AMC_Projectile_Arrow : public AActor
{
	GENERATED_BODY()
	
public:	
	AMC_Projectile_Arrow();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
};
