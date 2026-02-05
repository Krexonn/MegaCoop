// Copyright Krexonn


#include "UI/MC_WidgetComponent.h"

#include "AbilitySystem/MC_AbilitySystemComponent.h"
#include "AbilitySystem/MC_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/MC_BaseCharacter.h"
#include "UI/MC_AttributeWidget.h"


class UMC_AttributeWidget;
// Called when the game starts
void UMC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();


	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		MegaCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitializeAttributeDelegate();
}

void UMC_WidgetComponent::InitAbilitySystemData()
{
	MegaCharacter = Cast<AMC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UMC_AttributeSet>(MegaCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UMC_AbilitySystemComponent>(MegaCharacter->GetAbilitySystemComponent());
	
}

bool UMC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UMC_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributeInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}
void UMC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UMC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UMC_AttributeSet>(AS);

	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
}

void UMC_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(),Pair); // for checking the owned widget object.

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget,Pair);
		});
	}
}
void UMC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject,const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	//Check the user widget object owned by this component, see if it is a MC_AttributeWidget, handle it if so.
	UMC_AttributeWidget* AttributeWidget = Cast<UMC_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // We only care about CC_Attribute Widgets.
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe for matching Attributes.
	AttributeWidget->AvatarActor = MegaCharacter;
	
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), 0.f); // for initial values.

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue); // for changes during the game.
	});
}


