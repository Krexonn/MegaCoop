// Copyright Krexonn


#include "AbilitySystem/MC_AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameplayTags/MCTags.h"


void UMC_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxShieldCount, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME(ThisClass, bAttributesInitialized);
	
}

void UMC_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	HandleShieldBlock(Data);
	
	ClampAttributes(Data);
	
	HandleKillEvents(Data);
	
	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributeInitialized.Broadcast();
	}
	
}

void UMC_AttributeSet::ClampAttributes(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UMC_AttributeSet::HandleShieldBlock(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float Magnitude = Data.EvaluatedData.Magnitude;
		if (Magnitude < 0.0f)
		{
			UAbilitySystemComponent* TargetASC = &Data.Target;
			
			if (!TargetASC) return;

			FGameplayTag ShieldTag = FGameplayTag::RequestGameplayTag(FName("MCTags.Status.Shielded"));
			
			int32 ShieldCount = TargetASC->GetTagCount(ShieldTag);

			if (ShieldCount > 0)
			{
				SetHealth(GetHealth() - Magnitude);
				
				FGameplayEventData Payload;
				Payload.Instigator = Data.EffectSpec.GetEffectContext().GetInstigator();
                
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
					TargetASC->GetAvatarActor(), 
					FGameplayTag::RequestGameplayTag(FName("Event.Shield.Consumed")), 
					Payload
				);
			}
		}
	}
}

void UMC_AttributeSet::HandleKillEvents(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() <= 0.f)
	{
		FGameplayEventData Payload;
		Payload.Instigator = Data.Target.GetAvatarActor();
        
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Data.EffectSpec.GetEffectContext().GetInstigator(), 
			MCTags::Events::KillScored, 
			Payload
		);
	}
}

void UMC_AttributeSet::OnRep_AttributesInitialized()
{
	if (bAttributesInitialized)
	{
		OnAttributeInitialized.Broadcast();
	}
}

void UMC_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

void UMC_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}

void UMC_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue);
}

void UMC_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue);
}

void UMC_AttributeSet::OnRep_MaxShieldCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxShieldCount, OldValue);
}

void UMC_AttributeSet::OnRep_SpinningAxeCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, SpinningAxeCount, OldValue);
}

