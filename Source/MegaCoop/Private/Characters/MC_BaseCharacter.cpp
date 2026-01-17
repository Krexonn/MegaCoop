// Copyright Krexonn


#include "Characters/MC_BaseCharacter.h"

#include "Net/UnrealNetwork.h"


AMC_BaseCharacter::AMC_BaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}


void AMC_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAlive);
}


