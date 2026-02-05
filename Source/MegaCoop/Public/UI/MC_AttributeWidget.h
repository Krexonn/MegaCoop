// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/MC_AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "MC_AttributeWidget.generated.h"


/**
 * 
 */
UCLASS()
class MEGACOOP_API UMC_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "MegaC|Attributes")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "MegaC|Attributes")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UMC_AttributeSet* AttributeSet, float OldValue);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue, float OldValue);

	UPROPERTY(BlueprintReadOnly, Category= "MegaC|Attributes")
	TWeakObjectPtr<AActor> AvatarActor;
};
