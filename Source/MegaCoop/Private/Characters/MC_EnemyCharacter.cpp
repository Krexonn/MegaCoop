// Copyright Krexonn


#include "Characters/MC_EnemyCharacter.h"
#include "AbilitySystem/MC_AbilitySystemComponent.h"
#include "AbilitySystem/MC_AttributeSet.h"


AMC_EnemyCharacter::AMC_EnemyCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UMC_AbilitySystemComponent>("AbiltitySystemComponent");
	AbilitySystemComponent ->SetIsReplicated(true);
	AbilitySystemComponent ->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMC_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AMC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AMC_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}


void AMC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()-> InitAbilityActorInfo(this, this);
	

	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	InitializeAttributes();

	UMC_AttributeSet* CC_AttributeSet = Cast<UMC_AttributeSet>(GetAttributeSet());
	if (!IsValid(CC_AttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(CC_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	
}

