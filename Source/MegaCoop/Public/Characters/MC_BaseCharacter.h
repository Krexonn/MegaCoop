// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "MC_LightBaseCharacter.h"
#include "Abilities/GameplayAbility.h"
#include "Player/MC_PlayerState.h"
#include "MC_BaseCharacter.generated.h"

class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*,AS);
UCLASS()
class MEGACOOP_API AMC_BaseCharacter : public AMC_LightBaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMC_BaseCharacter();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }
	
	//bool IsAlive() { return bAlive; };
	//void SetAlive(bool bAliveStatus) { bAlive = bAliveStatus; };

	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;

	UFUNCTION(BlueprintCallable, Category="MegaCoop|Death")
	virtual void HandleRespawn();
	
	UFUNCTION(BlueprintCallable, Category="MegaCoop|Attribute")
	void ResetAttributes();
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;

	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	virtual void HandleOnDeath() override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:

	UPROPERTY(EditDefaultsOnly, Category= "MegaCoop|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;

	UPROPERTY(EditDefaultsOnly, Category = "MegaCoop|Effects")
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;
	
	//UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	//bool bAlive = true;
};
