// Copyright Krexonn


#include "Actors/Player/MC_SpiningAxe.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AMC_SpiningAxe::AMC_SpiningAxe()
{
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = LifeTime;
	
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(DefaultSceneRoot);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMC_SpiningAxe::OnOverlapBegin);
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(DefaultSceneRoot);
	SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 500.f; 
	ProjectileMovementComponent->MaxSpeed = 0.f;     
	ProjectileMovementComponent->ProjectileGravityScale = 0.f; 
	
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->RotationRate = FRotator(0.f, 1080.f, 0.f);
}

void AMC_SpiningAxe::BeginPlay()
{
	Super::BeginPlay();
}


void AMC_SpiningAxe::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetInstigator()) return;
	
	bool bIsEnemy = OtherActor->ActorHasTag(FName("Enemy"));
	if (bIsEnemy && !HitActors.Contains(OtherActor))
	{
		HitActors.Add(OtherActor);
		AActor* SourceActor = GetInstigator();
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		if (SourceASC && TargetASC && DamageEffectClass)
		{
			FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
			ContextHandle.AddInstigator(SourceActor, SourceActor); 
			FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, ContextHandle);
			
			FGameplayEventData EventData;
			EventData.Instigator = this;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor,FGameplayTag::RequestGameplayTag("MCTags.Events.Enemy.HitReact"), EventData);
			
			SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),TargetASC );
		}
		else
		{
			UGameplayStatics::ApplyDamage(
			OtherActor,
			ProjectileDamage,
			GetInstigatorController(), 
			this,                           
			UDamageType::StaticClass()
		);
			
		}
	}
	
	
}

// Called every frame


