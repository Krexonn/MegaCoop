// Copyright Krexonn


#include "AbilitySystem/Enemy/MC_HitReact.h"


void UMC_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();

	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();

	ToInstagtor = InstigatorLocation - AvatarLocation;
	ToInstagtor.Normalize();
}
