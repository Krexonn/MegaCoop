// Copyright Krexonn


#include "AbilitySystem/Player/MC_PrimaryAxe.h"

#include "AbilitySystem/MC_AttributeSet.h"
#include "Characters/MC_PlayerCharacter.h"

void UMC_PrimaryAxe::SpawnSpiningAxe()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetAvatarActorFromActorInfo();
	SpawnParams.Instigator = GetAvatarActorFromActorInfo()->GetInstigator();
	
	int32 LastIndex = GetProjectileCount();
	for (int i = 0; i < LastIndex; i++)
	{
		AMC_SpiningAxe* NewAxe = GetWorld()->SpawnActor<AMC_SpiningAxe>(
			SpiningAxeClass,
			CalculateSpawnTransform(i),
			SpawnParams
			);
		
	}
}

FTransform UMC_PrimaryAxe::CalculateSpawnTransform(int32 Index)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor) return FTransform();
	
	float OffsetMultiplier = ((static_cast<float>(Index))-((static_cast<float>(GetProjectileCount())-1.f) /2.f)); 
	
	FVector ProjectilesDistance = AvatarActor->GetActorRightVector() * SpreadDistance;
	FVector ProjectileLoc = ProjectilesDistance * OffsetMultiplier;
	FVector ActorLocation = AvatarActor->GetActorLocation() + AvatarActor->GetActorForwardVector() * 100.f; 
	FVector SpawnLocation = ActorLocation + ProjectileLoc;
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	
	FRotator SpawnRotation = AvatarActor->GetActorRotation();
	SpawnTransform.SetRotation(SpawnRotation.Quaternion());
	
	return SpawnTransform;
}

int32 UMC_PrimaryAxe::GetProjectileCount()
{
	AMC_PlayerCharacter* AvatarChar = Cast<AMC_PlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!AvatarChar) return 0;
	UMC_AttributeSet* MC_AttributeSet = Cast<UMC_AttributeSet>(AvatarChar->GetAttributeSet());
	if (!MC_AttributeSet) return 0;
	
	int32 SpinningAxeCount = FMath::RoundToInt(MC_AttributeSet->GetSpinningAxeCount());
	return SpinningAxeCount;
}
