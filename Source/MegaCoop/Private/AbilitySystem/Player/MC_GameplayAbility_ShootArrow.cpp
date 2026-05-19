// Copyright Krexonn

#include "AbilitySystem/Player/MC_GameplayAbility_ShootArrow.h"
#include "Actors/Player/MC_Projectile_Arrow.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

UMC_GameplayAbility_ShootArrow::UMC_GameplayAbility_ShootArrow()
{
	// Sunucuda çalıştırılıp client'lara senkronlanması için
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	TargetingRadius = 1000.f;
	FireRate = 1.0f;
}

void UMC_GameplayAbility_ShootArrow::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// Mermiyi sadece yetkili sunucu üzerinde atıyoruz. Yetenek aktifleştiğinde zamanlayıcıyı (timer) başlat.
	if (HasAuthority(&ActivationInfo))
	{
		// İlk atışı sıfırıncı saniyede yapıp (0.0f delay), sonrasında FireRate sıklığı ile loop (true) etmesini sağlıyoruz
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UMC_GameplayAbility_ShootArrow::FireArrow, FireRate, true, 0.0f);
	}
}

void UMC_GameplayAbility_ShootArrow::FireArrow()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor || !ProjectileClass)
	{
		return;
	}

	FVector MuzzleLocation = AvatarActor->GetActorLocation(); 
	
	// Hedef Arama (Targeting)
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AvatarActor);
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(
		AvatarActor,
		MuzzleLocation,
		TargetingRadius,
		TargetObjectTypes,
		AActor::StaticClass(),
		ActorsToIgnore,
		OutActors
	);

	AActor* ClosestEnemy = nullptr;
	float ClosestDistanceSq = MAX_flt;

	// En yakın düşmanı bul
	for (AActor* OverlappedActor : OutActors)
	{
		if (OverlappedActor && OverlappedActor != AvatarActor)
		{
			float DistSq = FVector::DistSquared(MuzzleLocation, OverlappedActor->GetActorLocation());
			if (DistSq < ClosestDistanceSq)
			{
				ClosestDistanceSq = DistSq;
				ClosestEnemy = OverlappedActor;
			}
		}
	}

	FVector Direction;
	
	// Yön Belirleme (Direction Logic)
	if (ClosestEnemy)
	{
		// Düşmana doğru vektör
		Direction = (ClosestEnemy->GetActorLocation() - MuzzleLocation).GetSafeNormal2D();
	}
	else
	{
		// Düşman yoksa rastgele 2D vektör
		float RandomAngle = FMath::RandRange(0.f, 360.f);
		Direction = FVector(FMath::Cos(FMath::DegreesToRadians(RandomAngle)), FMath::Sin(FMath::DegreesToRadians(RandomAngle)), 0.f);
	}

	FRotator ProjectileRotation = Direction.Rotation();
	FTransform SpawnTransform(ProjectileRotation, MuzzleLocation);

	// Server'da mermiyi dünyaya dahil etme
	AMC_Projectile_Arrow* SpawnedProjectile = GetWorld()->SpawnActorDeferred<AMC_Projectile_Arrow>(
		ProjectileClass,
		SpawnTransform,
		AvatarActor,
		Cast<APawn>(AvatarActor),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (SpawnedProjectile)
	{
		SpawnedProjectile->FinishSpawning(SpawnTransform);
	}
}

void UMC_GameplayAbility_ShootArrow::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Yetenek iptal edildiğinde (CancelAbility) Timer'ı kapatıp kaynakları temizliyoruz.
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
