// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "MC_AttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributeInitialized);


UCLASS()
class MEGACOOP_API UMC_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	FAttributeInitialized OnAttributeInitialized;

	UPROPERTY(ReplicatedUsing = OnRep_AttributesInitialized)
	bool bAttributesInitialized = false;

	UFUNCTION()
	void OnRep_AttributesInitialized();
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShieldCount)
	FGameplayAttributeData MaxShieldCount;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpinningAxeCount)
	FGameplayAttributeData SpinningAxeCount;
	

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxShieldCount(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_SpinningAxeCount(const FGameplayAttributeData& OldValue);
	
	
	
	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);
	
	ATTRIBUTE_ACCESSORS(ThisClass, MaxShieldCount);
	ATTRIBUTE_ACCESSORS(ThisClass, SpinningAxeCount);
	
protected:
	
	void ClampAttributes(const FGameplayEffectModCallbackData& Data);
	
	void HandleShieldBlock(const FGameplayEffectModCallbackData& Data);
	
	void HandleKillEvents(const FGameplayEffectModCallbackData& Data);
};
