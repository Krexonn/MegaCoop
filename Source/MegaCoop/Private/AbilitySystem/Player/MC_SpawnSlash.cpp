// Copyright Krexonn


#include "AbilitySystem/Player/MC_SpawnSlash.h"
#include "AbilitySystemComponent.h"

UMC_SpawnSlash::UMC_SpawnSlash()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}


void UMC_SpawnSlash::SpawnSlashActor()
{
    AActor* AvatarActor = GetAvatarActorFromActorInfo();
    if (!AvatarActor || !SlashActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("MegaCoop: Avatar veya SlashActorClass eksik!"));
        return;
    }
    
    FGameplayEffectSpecHandle DamageSpecHandle;
    if (DamageEffectClass)
    {
        DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass);
    }
    
    for (int32 i = 0; i < SlashCount; i++)
    {
        FVector SpawnLocation = AvatarActor->GetActorLocation();
        SpawnLocation.Z += 50.0f;
        FRotator SpawnRotation = FRotator::ZeroRotator;

        if (i == 0)
        {
            SpawnRotation = AvatarActor->GetActorRotation();
            SpawnRotation.Pitch = 0.0f;
            SpawnRotation.Roll = 0.0f;
        }
        else
        {
            SpawnRotation.Yaw = FMath::RandRange(0.0f, 360.0f);
        }
        
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
            
            if (DamageSpecHandle.IsValid())
            {
                SlashActor->SetDamageSpec(DamageSpecHandle);
            }
        }
    }
}
