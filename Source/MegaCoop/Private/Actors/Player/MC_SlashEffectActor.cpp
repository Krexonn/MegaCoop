// Copyright Krexonn


#include "Actors/Player/MC_SlashEffectActor.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMC_SlashEffectActor::AMC_SlashEffectActor()
{
	PrimaryActorTick.bCanEverTick = true; 

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneComponent;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(RootComponent); 
	
	USceneComponent* RotatingPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotatingPivot"));
	RotatingPivot->SetupAttachment(RootComponent);
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(RotatingPivot);
	
	CollisionComp->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f)); 
	CollisionComp->SetBoxExtent(FVector(100.0f, 40.0f, 5.0f));
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComp"));
	RotationComp->SetUpdatedComponent(RotatingPivot); 
    
	RotationComp->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

	InitialLifeSpan = 0.3f;
}


void AMC_SlashEffectActor::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMC_SlashEffectActor::OnOverlapBegin);
}
void AMC_SlashEffectActor::SetDamageSpec(FGameplayEffectSpecHandle Handle)
{
	DamageEffectSpecHandle = Handle;
}

void AMC_SlashEffectActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//AMC_EnemyCharacter* Enemy = Cast<AMC_EnemyCharacter>(OtherActor);
	bool bIsEnemy = OtherActor->ActorHasTag(FName("Enemy"));
	
	if (OtherActor && OtherActor != GetInstigator() && !HitActors.Contains(OtherActor) && bIsEnemy)
	{
		HitActors.Add(OtherActor);
		
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
        
		if (TargetASC && DamageEffectSpecHandle.IsValid())
		{
			TargetASC->ApplyGameplayEffectSpecToTarget(*DamageEffectSpecHandle.Data.Get(), TargetASC);
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

