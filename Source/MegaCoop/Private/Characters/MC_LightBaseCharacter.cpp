// Copyright Krexonn


#include "Characters/MC_LightBaseCharacter.h"
#include "Net/UnrealNetwork.h"

void AMC_LightBaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bAlive);
}

void AMC_LightBaseCharacter::HandleOnDeath()
{
}
