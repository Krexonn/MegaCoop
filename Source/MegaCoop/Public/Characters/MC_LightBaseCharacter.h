// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MC_LightBaseCharacter.generated.h"

UCLASS()
class MEGACOOP_API AMC_LightBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	bool IsAlive() const { return bAlive; }
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(BlueprintCallable, Category = "MegaCoop|State")
	void SetAlive(bool bAliveStatus) { bAlive = bAliveStatus; }
	
	virtual void HandleOnDeath();

	
protected:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive = true;


};
