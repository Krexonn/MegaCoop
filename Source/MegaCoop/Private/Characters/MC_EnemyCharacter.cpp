// Copyright Krexonn


#include "Characters/MC_EnemyCharacter.h"
#include "AbilitySystem/MC_AbilitySystemComponent.h"


AMC_EnemyCharacter::AMC_EnemyCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UMC_AbilitySystemComponent>("AbiltitySystemComponent");
	AbilitySystemComponent ->SetIsReplicated(true);
	AbilitySystemComponent ->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AMC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AMC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()-> InitAbilityActorInfo(this, this);
	

	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	
}

