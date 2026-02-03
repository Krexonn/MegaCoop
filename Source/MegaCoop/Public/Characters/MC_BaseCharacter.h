// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Player/MC_PlayerState.h"
#include "MC_BaseCharacter.generated.h"

class UGameplayAbility;
UCLASS()
class MEGACOOP_API AMC_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMC_BaseCharacter();
	
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }
	
	bool IsAlive() { return bAlive; };
	void SetAlive(bool bAliveStatus) { bAlive = bAliveStatus; };
protected:
	void GiveStartupAbilities();
private:

	UPROPERTY(EditDefaultsOnly, Category= "MC|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive = true;
};
