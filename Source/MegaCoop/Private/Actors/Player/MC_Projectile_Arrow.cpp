// Copyright Krexonn

#include "Actors/Player/MC_Projectile_Arrow.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMC_Projectile_Arrow::AMC_Projectile_Arrow()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Multiplayer replication
	bReplicates = true;
	SetReplicatingMovement(true);

	// Sphere Collision
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComponent->SetGenerateOverlapEvents(true);

	// Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Projectile Movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->ProjectileGravityScale = 0.f; // Arrow moves straight in 2D
}

void AMC_Projectile_Arrow::BeginPlay()
{
	Super::BeginPlay();

	// Server only collision binding for damage
	if (HasAuthority())
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMC_Projectile_Arrow::OnProjectileOverlap);
	}
}

void AMC_Projectile_Arrow::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator() && OtherActor != this)
	{
		// TODO: Apply GameplayEffect or Damage to the OtherActor here

		// Destroy the projectile upon hitting an enemy
		Destroy();
	}
}
