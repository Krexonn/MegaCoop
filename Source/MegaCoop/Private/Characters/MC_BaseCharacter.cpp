// Copyright Krexonn


#include "Characters/MC_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


AMC_BaseCharacter::AMC_BaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AMC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AMC_BaseCharacter::ResetAttributes()
{
	checkf(IsValid(ResetAttributesEffect), TEXT("ResetAttributesEffect not set."));
	if (!IsValid((GetAbilitySystemComponent()))) return;

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(ResetAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AMC_BaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent()))return;
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void AMC_BaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set."));

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AMC_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f)
	{
		HandleOnDeath();
	}
}

void AMC_BaseCharacter::HandleOnDeath()
{
	bAlive = false;
}


void AMC_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAlive);
}


