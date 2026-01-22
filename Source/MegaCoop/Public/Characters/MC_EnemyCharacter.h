// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "MC_BaseCharacter.h"
#include "MC_EnemyCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class MEGACOOP_API AMC_EnemyCharacter : public AMC_BaseCharacter
{
	GENERATED_BODY()

public:
	
	AMC_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
