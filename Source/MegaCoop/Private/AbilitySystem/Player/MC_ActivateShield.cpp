// Copyright Krexonn


#include "AbilitySystem/Player/MC_ActivateShield.h"
#include "AbilitySystem/MC_AttributeSet.h"
#include "Actors/Player/MC_OrbitalShield.h"
#include "Characters/MC_PlayerCharacter.h"



void UMC_ActivateShield::CheckAndSpawnShield()
{
	AMC_PlayerCharacter* AvatarChar = Cast<AMC_PlayerCharacter>(GetAvatarActorFromActorInfo());
	if (!AvatarChar) return;
	UMC_AttributeSet* MC_AttributeSet = Cast<UMC_AttributeSet>(AvatarChar->GetAttributeSet());
	if (!MC_AttributeSet) return;
	
	int32 MaxShields = FMath::RoundToInt(MC_AttributeSet->GetMaxShieldCount());
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("Attribute Max Shields: %d"), MaxShields));
	
	ActiveShields.Remove(nullptr);
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
	if (ShieldRef)
	{
		ActiveShields.Remove(ShieldRef);
	}
	ActiveShields.Remove(nullptr);
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC && ShieldActiveEffectHandle.IsValid())
	{
		// 1 Stack sil (Kaçak silinmelerde bile buff sayısının doğru kalmasını sağlar)
		ASC->RemoveActiveGameplayEffect(ShieldActiveEffectHandle, 1);
	}
	
	// Bir kalkan eksildiği için açıları yeniden dağıt
	SetCurrentAngle(ActiveShields.Num());
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

void UMC_ActivateShield::SetCurrentAngle(int ShieldCount)
{
	if (ShieldCount <= 0) return;
	
	for (int32 i = 0; i < ShieldCount; ++i)
	{
		int Angle = (i * 360) / ShieldCount;		
		
		if (ActiveShields.IsValidIndex(i))
		{
			AMC_OrbitalShield* ShieldRef = ActiveShields[i];
			if (ShieldRef)
			{
				ShieldRef->CurrentAngle = Angle;
			}
		}
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
	GEngine->AddOnScreenDebugMessage(-1, 2.f,FColor::Cyan, "Active Shield Effect");
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::FromInt(CheckStackCount(ShieldActiveEffectHandle)) );
	SetCurrentAngle(ActiveShields.Num());
}
