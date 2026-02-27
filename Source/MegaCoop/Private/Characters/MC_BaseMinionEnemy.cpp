// Copyright Krexonn


#include "Characters/MC_BaseMinionEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"


AMC_BaseMinionEnemy::AMC_BaseMinionEnemy()
{
	
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
}

void AMC_BaseMinionEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TargetPlayer)
	{
		FVector DirectionToPlayer = (TargetPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		
		AddMovementInput(DirectionToPlayer, 1.0f);
	}
}


void AMC_BaseMinionEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void AMC_BaseMinionEnemy::HandleOnDeath()
{
	Super::HandleOnDeath();
	SetAlive(false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Minion Dead!"));
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	
	SetActorTickEnabled(false); 
	
	TargetPlayer = nullptr;
}

void AMC_BaseMinionEnemy::ResetEnemy(AActor* NewTarget)
{
	CurrentHealth = MaxHealth; 
	SetAlive(true);
	TargetPlayer = NewTarget;
	
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	
	SetActorTickEnabled(true);
}

float AMC_BaseMinionEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("TakeDamage: %f"), ActualDamage));
	if (ActualDamage > 0.f && IsAlive())
	{
		CurrentHealth -= ActualDamage;
		
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Minion Hasar Aldı: %f, Kalan Can: %f"), ActualDamage, CurrentHealth));

		if (CurrentHealth <= 0.0f)
		{
			HandleOnDeath(); 
		}
	}
	return ActualDamage;
}


