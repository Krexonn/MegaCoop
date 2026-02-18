// Copyright Krexonn


#include "Utils/MC_BlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UMC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	if (Dot < 0.5f)
	{
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}
	return EHitDirection::Forward;
}

FName UMC_BlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Back: return FName("Back");
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Forward: return FName("Forward");
	default: return FName("None");
	}
}

void UMC_BlueprintLibrary::ApplyHybridDamage(AActor* SourceActor, AActor* TargetActor, float BaseDamage,
	const FGameplayEffectSpecHandle& DamageEffectSpec)
{
	if (!SourceActor || !TargetActor) return;
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	if (TargetASC && DamageEffectSpec.IsValid())
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpec.Data.Get());
	}
	else
	{
		UGameplayStatics::ApplyDamage(
			TargetActor,
			BaseDamage,
			SourceActor->GetInstigatorController(), 
			SourceActor,                           
			UDamageType::StaticClass()
		);
	}
}
