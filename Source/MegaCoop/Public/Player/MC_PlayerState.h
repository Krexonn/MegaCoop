// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "MC_PlayerState.generated.h"

class UAbilitySystemComponent;
UCLASS()
class MEGACOOP_API AMC_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AMC_PlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	

private:

	UPROPERTY(VisibleAnywhere, Category="MC|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
