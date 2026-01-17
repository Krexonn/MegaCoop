// Copyright Krexonn


#include "Characters/MC_BaseCharacter.h"



AMC_BaseCharacter::AMC_BaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}





