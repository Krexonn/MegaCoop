// Copyright Krexonn


#include "Actors/Player/MC_OrbitalShield.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/MC_PlayerCharacter.h"
#include "Components/SphereComponent.h"


AMC_OrbitalShield::AMC_OrbitalShield()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    RootComponent = CollisionComp;
    
    CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic")); 

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMeshComp->SetupAttachment(RootComponent);
    SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMC_OrbitalShield::OnOverlapBegin);
}

void AMC_OrbitalShield::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (OwnerCharacter)
    {
        CurrentAngle += RotationSpeed * DeltaTime;
        if (CurrentAngle >= 360.0f) CurrentAngle -= 360.0f;
        
        float Radian = FMath::DegreesToRadians(CurrentAngle);

        FVector OwnerLoc = OwnerCharacter->GetActorLocation();
        
        FVector NewLoc;
        NewLoc.X = OwnerLoc.X + FMath::Cos(Radian) * Radius;
        NewLoc.Y = OwnerLoc.Y + FMath::Sin(Radian) * Radius;
        NewLoc.Z = OwnerLoc.Z + VerticalOffset;

        SetActorLocation(NewLoc);
        FVector OutwardVector = NewLoc - OwnerLoc;
        FRotator NewRot = OutwardVector.Rotation();
    
        NewRot.Pitch = 0.0f;
        NewRot.Roll = 0.0f;
        SetActorRotation(NewRot);
    }
}

void AMC_OrbitalShield::UpdateShieldPosition(float NewAngle, float NewRadius, float NewHeight)
{
    // Bu fonksiyonu Karakterimiz her karede (veya değişimde) çağıracak
    if (!OwnerCharacter) return;

    float Radian = FMath::DegreesToRadians(NewAngle);
    FVector OwnerLoc = OwnerCharacter->GetActorLocation();

    FVector NewLoc;
    NewLoc.X = OwnerLoc.X + FMath::Cos(Radian) * NewRadius;
    NewLoc.Y = OwnerLoc.Y + FMath::Sin(Radian) * NewRadius;
    NewLoc.Z = OwnerLoc.Z + NewHeight;

    SetActorLocation(NewLoc);

    // Dışarı bakması için rotasyon (Senin istediğin dışa bakma kodu)
    FVector OutwardVector = NewLoc - OwnerLoc;
    FRotator NewRot = OutwardVector.Rotation();
    NewRot.Pitch = 0.0f; 
    NewRot.Roll = 0.0f;
    SetActorRotation(NewRot);
}

void AMC_OrbitalShield::BeginPlay()
{
    Super::BeginPlay();
}

void AMC_OrbitalShield::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                       bool bFromSweep, const FHitResult& SweepResul)
{
    AMC_PlayerCharacter* PlayerCharacter = Cast<AMC_PlayerCharacter>(OtherActor);
    if (OtherActor && OtherActor != OwnerCharacter && OtherActor != PlayerCharacter)
    {
        UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);

        if (SourceASC && TargetASC && DamageEffectClass)
        {
            FGameplayEffectContextHandle Context = SourceASC->MakeEffectContext();
            Context.AddSourceObject(this);
            
            SourceASC->ApplyGameplayEffectToTarget(DamageEffectClass.GetDefaultObject(), TargetASC, 1.0f, Context);
            
            Destroy(); 
            
            FGameplayEventData EventData;
            EventData.Instigator = this;
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FGameplayTag::RequestGameplayTag("MCTags.Events.Player.Shield.Consumed"), EventData);
        }
    }
}
