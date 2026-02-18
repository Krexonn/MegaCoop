// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionComp;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
