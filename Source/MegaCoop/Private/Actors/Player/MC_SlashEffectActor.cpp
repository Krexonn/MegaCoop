// Copyright Krexonn


#include "Actors/Player/MC_SlashEffectActor.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AMC_SlashEffectActor::AMC_SlashEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(RootComponent);
	
	InitialLifeSpan = 0.5f;
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
	if (OtherActor && OtherActor != GetInstigator() && !HitActors.Contains(OtherActor))
	{
		HitActors.Add(OtherActor);
		
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
        
		if (TargetASC && DamageEffectSpecHandle.IsValid())
		{
			TargetASC->ApplyGameplayEffectSpecToTarget(*DamageEffectSpecHandle.Data.Get(), TargetASC);
		}
	}
}

