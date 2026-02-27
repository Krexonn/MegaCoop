// Copyright Krexonn


#include "Actors/Enemy/MC_EnemySpawner.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "NavigationSystem.h"
#include "Characters/MC_BaseMinionEnemy.h"


// Sets default values
AMC_EnemySpawner::AMC_EnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMC_EnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority() && SpawnerStarted)
	{
		InitializePool(); 
		
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AMC_EnemySpawner::ActivateEnemyFromPool, SpawnInterval, true);
	}
}

void AMC_EnemySpawner::InitializePool()
{
	if (!EnemyClassToSpawn) return;

	for (int32 i = 0; i < PoolSize; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		AActor* NewEnemy = GetWorld()->SpawnActor<AActor>(EnemyClassToSpawn, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
        
		if (NewEnemy)
		{
			NewEnemy->SetActorHiddenInGame(true); 
			NewEnemy->SetActorEnableCollision(false); 
			NewEnemy->SetActorTickEnabled(false); 
            
			EnemyPool.Add(NewEnemy);
		}
	}
}

void AMC_EnemySpawner::ActivateEnemyFromPool()
{
	AActor* AvailableEnemy = nullptr;
	for (AActor* Enemy : EnemyPool)
	{
		if (Enemy && Enemy->IsHidden()) 
		{
			AvailableEnemy = Enemy;
			break;
		}
	}
	
	if (!AvailableEnemy) return;
	
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (!GameState || GameState->PlayerArray.IsEmpty()) return;

	int32 RandomPlayerIndex = FMath::RandRange(0, GameState->PlayerArray.Num() - 1);
	APlayerState* TargetPlayerState = GameState->PlayerArray[RandomPlayerIndex];
	if (!TargetPlayerState || !TargetPlayerState->GetPawn()) return;

	APawn* TargetPlayer = TargetPlayerState->GetPawn();
	
	float RandomAngle = FMath::RandRange(0.0f, 360.0f);
	FVector RandomDirection(FMath::Cos(RandomAngle), FMath::Sin(RandomAngle), 0.f);
	FVector TargetSpawnLocation = TargetPlayer->GetActorLocation() + (RandomDirection * SpawnRadius);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation SafeLocation;
	if (NavSystem && NavSystem->ProjectPointToNavigation(TargetSpawnLocation, SafeLocation, FVector(500.f)))
	{
		TargetSpawnLocation = SafeLocation.Location;
	}
	
	AvailableEnemy->SetActorLocation(TargetSpawnLocation);
	AvailableEnemy->SetActorHiddenInGame(false);
	AvailableEnemy->SetActorEnableCollision(true);
	AvailableEnemy->SetActorTickEnabled(true);
	
	if (AMC_BaseMinionEnemy* Minion = Cast<AMC_BaseMinionEnemy>(AvailableEnemy))
	{
		Minion->ResetEnemy(TargetPlayer);
	}
	
}




