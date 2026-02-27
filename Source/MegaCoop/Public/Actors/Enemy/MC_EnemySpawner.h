// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MC_EnemySpawner.generated.h"

UCLASS()
class MEGACOOP_API AMC_EnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMC_EnemySpawner();
	
	UPROPERTY(EditAnywhere, Category = "MegaCoop|Spawning")
	bool SpawnerStarted = true;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Spawning")
	TSubclassOf<class AActor> EnemyClassToSpawn;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Spawning")
	float SpawnInterval = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Spawning")
	float SpawnRadius = 1500.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Pool")
	int32 PoolSize = 100;
	
	UPROPERTY()
	TArray<AActor*> EnemyPool;
	
	void InitializePool();
	
	UFUNCTION()
	void ActivateEnemyFromPool();

private:
	// Zamanlayıcıyı tutacak olan değişken (Tick yerine bunu kullanıyoruz)
	FTimerHandle SpawnTimerHandle;
};
