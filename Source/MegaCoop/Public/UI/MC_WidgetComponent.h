// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MC_WidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MEGACOOP_API UMC_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<AMC_BaseCharacter> MegaCharacter;
	TWeakObjectPtr<UMC_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UMC_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair)const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();

};
