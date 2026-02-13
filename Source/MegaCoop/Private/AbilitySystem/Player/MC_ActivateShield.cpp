// Copyright Krexonn


#include "AbilitySystem/Player/MC_ActivateShield.h"

#include "AbilitySystem/MC_AttributeSet.h"
#include "Actors/Player/MC_OrbitalShield.h"


void UMC_ActivateShield::CheckAndSpawnShield()
{
	if (!AttributeSet) return;
	int32 MaxShields = FMath::RoundToInt(AttributeSet->GetMaxShieldCount());
	
	
	if (ActiveShields.Num() < MaxShields)
	{
		SpawnSingleShield();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("New Shield Spawned!"));
	}
}

void UMC_ActivateShield::GetTimerEvent()
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_ShieldRegen, 
		this, 
		&UMC_ActivateShield::CheckAndSpawnShield, 
		ShieldCheckInterval, 
		true
	);
	
}

void UMC_ActivateShield::SpawnSingleShield()
{
	if (!ShieldClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("MC_OrbitalShields none!"));
		return;
	}
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor) return;
	FVector SpawnLoc = AvatarActor->GetActorLocation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetAvatarActorFromActorInfo();
	SpawnParams.Instigator = GetAvatarActorFromActorInfo()->GetInstigator();
	
	
	AMC_OrbitalShield* NewShield = GetWorld()->SpawnActor<AMC_OrbitalShield>(
		ShieldClass, 
		SpawnLoc, 
		FRotator::ZeroRotator, 
		SpawnParams
	);
	
	if (NewShield)
	{
		ActiveShields.Add(NewShield);
		NewShield->OwnerCharacter = GetAvatarActorFromActorInfo();
	}
}

void UMC_ActivateShield::CheckStackCount(FActiveGameplayEffectHandle ActiveHandle) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

	if (ASC)
	{
		int32 StackCount = ASC->GetCurrentStackCount(ActiveHandle);

		UE_LOG(LogTemp, Warning, TEXT("Stack Count: %d"), StackCount);
	}
}

void UMC_ActivateShield::SetCurrentAngel(int LastIndex)
{
	for (int i = 1; i < LastIndex; ++i)
	{
		int index = i-1;
		int Angel = (i * 360)/LastIndex;		
		
		AMC_OrbitalShield* shield = ActiveShields[index];
		shield->CurrentAngle = Angel;
	}
}

void UMC_ActivateShield::ApplyShieldEffect()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC && ShieldEffectClass)
	{
		
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ShieldEffectClass, 1.0f, Context);

		if (SpecHandle.IsValid())
		{
			ShieldEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	
}
