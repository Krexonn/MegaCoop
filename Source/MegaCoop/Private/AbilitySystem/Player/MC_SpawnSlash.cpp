// Copyright Krexonn


#include "AbilitySystem/Player/MC_SpawnSlash.h"
#include "AbilitySystemComponent.h"

UMC_SpawnSlash::UMC_SpawnSlash()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMC_SpawnSlash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    AActor* AvatarActor = ActorInfo->AvatarActor.Get();
    if (!AvatarActor || !SlashActorClass) return;
    
    FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass);
    
    // (Opsiyonel) Hasar miktarını burada dinamik olarak da set edebilirsin:
    // DamageSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), 50.0f);
    
    for (int32 i = 0; i < SlashCount; i++)
    {
        FVector SpawnLocation = AvatarActor->GetActorLocation();
        FRotator SpawnRotation = FRotator::ZeroRotator;

        // Rastgelelik ekle (Karakterin etrafında rastgele yönlerde çıksın)
        SpawnRotation.Yaw = FMath::RandRange(0.0f, 360.0f);
        
        // Hafif ileri öteleme (Karakterin içinden değil, önünden çıksın)
        FVector ForwardOffset = SpawnRotation.Vector() * 100.0f; 
        SpawnLocation += ForwardOffset;

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = AvatarActor;
        SpawnParams.Instigator = Cast<APawn>(AvatarActor);

        AMC_SlashEffectActor* SlashActor = GetWorld()->SpawnActor<AMC_SlashEffectActor>(SlashActorClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (SlashActor)
        {
            SlashActor->SetActorScale3D(FVector(SlashSizeScale));
            
            SlashActor->SetDamageSpec(DamageSpecHandle);
        }
    }
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}