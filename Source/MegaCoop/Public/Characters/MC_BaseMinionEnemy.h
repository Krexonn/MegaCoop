// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "MC_LightBaseCharacter.h"
#include "MC_BaseMinionEnemy.generated.h"

UCLASS()
class MEGACOOP_API AMC_BaseMinionEnemy : public AMC_LightBaseCharacter
{
	GENERATED_BODY()

public:
	AMC_BaseMinionEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MegaCoop|Stats")
	float MaxHealth = 100.0f;
	
	virtual void HandleOnDeath() override;
	
	void ResetEnemy(AActor* NewTarget);

protected:
	virtual void Tick(float DeltaTime) override;
	
	float CurrentHealth;

	virtual void BeginPlay() override;
	
	

	virtual float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser) override;
	
public:
	UPROPERTY()
	AActor* TargetPlayer;
};