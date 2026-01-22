// Copyright Krexonn


#include "Player/MC_PlayerState.h"
#include "AbilitySystem/MC_AbilitySystemComponent.h"

AMC_PlayerState::AMC_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	
	AbilitySystemComponent = CreateDefaultSubobject<UMC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AMC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

