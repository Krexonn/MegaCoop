// Copyright Krexonn


#include "AbilitySystem/Player/MC_ActivateShield.h"

#include "AbilitySystem/MC_AttributeSet.h"
#include "Actors/Player/MC_OrbitalShield.h"
#include "Characters/MC_PlayerCharacter.h"
#include "Net/UnrealNetwork.h"


void UMC_ActivateShield::CheckAndSpawnShield()
{
	AMC_PlayerCharacter* AvatarChar = Cast<AMC_PlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!AvatarChar) return;
	UMC_AttributeSet* MC_AttributeSet = Cast<UMC_AttributeSet>(AvatarChar->GetAttributeSet());
    
	if (!MC_AttributeSet) return;
	int32 MaxShields = FMath::RoundToInt(MC_AttributeSet->GetMaxShieldCount());
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::FromInt(MaxShields) );
	
	
	if (ActiveShields.Num() < MaxShields)
	{
		SpawnSingleShield();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("New Shield Spawned!"));
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::FromInt(ActiveShields.Num()) );
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Maximum shielding has been created.") );
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::FromInt(ActiveShields.Num()) );
	}
}

void UMC_ActivateShield::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UMC_ActivateShield, ActiveShields);
}

void UMC_ActivateShield::GetTimerEvent()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor && !AvatarActor->HasAuthority()) 
	{
		return;
	}
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_ShieldRegen, 
		this, 
		&UMC_ActivateShield::CheckAndSpawnShield, 
		ShieldCheckInterval, 
		true
	);
	
}

void UMC_ActivateShield::DeleteShieldRef(AMC_OrbitalShield* ShieldRef)
{
	ActiveShields.Remove(ShieldRef);
}

void UMC_ActivateShield::SpawnSingleShield()
{
	if (!ShieldClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("MC_OrbitalShields none!"));
		return;
	}
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor) return;
	FVector SpawnLoc = AvatarActor->GetActorLocation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetAvatarActorFromActorInfo();
	SpawnParams.Instigator = GetAvatarActorFromActorInfo()->GetInstigator();
	
	
	AMC_OrbitalShield* NewShield = GetWorld()->SpawnActor<AMC_OrbitalShield>(
		ShieldClass, 
		SpawnLoc, 
		FRotator::ZeroRotator, 
		SpawnParams
	);
	
	if (NewShield)
	{
		ActiveShields.Add(NewShield);
		NewShield->OwnerCharacter = GetAvatarActorFromActorInfo();
	}
	ApplyShieldEffect();
	
}

int UMC_ActivateShield::CheckStackCount(FActiveGameplayEffectHandle ActiveHandle) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

	if (ASC)
	{
		int32 StackCount = ASC->GetCurrentStackCount(ActiveHandle);

		UE_LOG(LogTemp, Warning, TEXT("Stack Count: %d"), StackCount);
		return StackCount;
	}
	return 0;
}

void UMC_ActivateShield::SetCurrentAngle(int LastIndex)
{
	if (LastIndex <= 0) return;
	for (int32 i = 1; i < LastIndex; ++i)
	{
		int32 index = i-1;
		int Angle = (i * 360)/LastIndex;		
		
		if (!ActiveShields.IsValidIndex(index)) return;
		AMC_OrbitalShield* ShieldRef = ActiveShields[index];
		if (!ShieldRef) return;
		
		ShieldRef->CurrentAngle = Angle;
	}
}

void UMC_ActivateShield::ApplyShieldEffect()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC && ShieldStackEffectClass)
	{
		
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ShieldStackEffectClass, 1.0f, Context);

		if (SpecHandle.IsValid())
		{
			ShieldActiveEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	//Debug
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::FromInt(CheckStackCount(ShieldActiveEffectHandle)) );
	SetCurrentAngle(CheckStackCount(ShieldActiveEffectHandle));
}
