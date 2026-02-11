// Copyright Krexonn


#include "Actors/Player/MC_OrbitalShield.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"


AMC_OrbitalShield::AMC_OrbitalShield()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    RootComponent = CollisionComp;
    
    // Sadece düşmanları algıla (Pawn kanalını overlap yap, WorldStatic blokla vs.)
    CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic")); 

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Mesh collision yapmasın
    
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
        // 1. Açı güncelleme
        CurrentAngle += RotationSpeed * DeltaTime;
        if (CurrentAngle >= 360.0f) CurrentAngle -= 360.0f;

        // 2. Yeni pozisyon hesaplama (Matematiksel Dönüşüm)
        // Radyan cinsinden açıya ihtiyaç var
        float Radian = FMath::DegreesToRadians(CurrentAngle);

        FVector OwnerLoc = OwnerCharacter->GetActorLocation();
        
        FVector NewLoc;
        NewLoc.X = OwnerLoc.X + FMath::Cos(Radian) * Radius;
        NewLoc.Y = OwnerLoc.Y + FMath::Sin(Radian) * Radius;
        NewLoc.Z = OwnerLoc.Z + VerticalOffset;

        SetActorLocation(NewLoc);
        
        // İstersen kalkanın yüzü hep dışarı baksın:
        FRotator NewRot = (NewLoc - OwnerLoc).Rotation();
        SetActorRotation(NewRot);
    }
}

void AMC_OrbitalShield::BeginPlay()
{
    Super::BeginPlay();
}

void AMC_OrbitalShield::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                       bool bFromSweep, const FHitResult& SweepResul)
{
    if (OtherActor && OtherActor != OwnerCharacter)
    {
        // GAS üzerinden hasar ver
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
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FGameplayTag::RequestGameplayTag("Event.Shield.Consumed"), EventData);
        }
    }
}
