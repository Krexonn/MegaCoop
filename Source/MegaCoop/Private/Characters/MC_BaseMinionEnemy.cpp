// Copyright Krexonn


#include "Characters/MC_BaseMinionEnemy.h"



AMC_BaseMinionEnemy::AMC_BaseMinionEnemy()
{
	
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Minion is Death!"));
}

float AMC_BaseMinionEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("TakeDamage: %f"), ActualDamage));
	if (ActualDamage > 0.f && IsAlive())
	{
		CurrentHealth -= ActualDamage;
        
		// Basit bir Debug yazısı (İşe yaradığını görmek için)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Minion Hasar Aldı: %f, Kalan Can: %f"), ActualDamage, CurrentHealth));

		if (CurrentHealth <= 0.0f)
		{
			HandleOnDeath(); 
		}
	}
	return ActualDamage;
}


