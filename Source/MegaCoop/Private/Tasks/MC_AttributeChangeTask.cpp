// Copyright Krexonn

#include "Tasks/MC_AttributeChangeTask.h"
#include "AbilitySystemComponent.h"




UMC_AttributeChangeTask* UMC_AttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbiltiySystemComponent, FGameplayAttribute Attribute)
{
	UMC_AttributeChangeTask* WaitForAttributeChangeTask = NewObject<UMC_AttributeChangeTask>();
	WaitForAttributeChangeTask->ASC = AbiltiySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbiltiySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}

	AbiltiySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &UMC_AttributeChangeTask::AttributeChanged);

	return WaitForAttributeChangeTask;
}

void UMC_AttributeChangeTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkAsGarbage();
	
}

void UMC_AttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
