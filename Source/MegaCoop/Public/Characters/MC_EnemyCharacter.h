// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "MC_BaseCharacter.h"
#include "MC_EnemyCharacter.generated.h"

class UAbilitySystemComponent;
class  UAttributeSet;

UCLASS()
class MEGACOOP_API AMC_EnemyCharacter : public AMC_BaseCharacter
{
	GENERATED_BODY()

public:
	
	AMC_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
protected:

	virtual void BeginPlay() override;
	
	virtual void HandleOnDeath() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
