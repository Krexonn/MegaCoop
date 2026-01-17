// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MC_BaseCharacter.generated.h"

UCLASS()
class MEGACOOP_API AMC_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMC_BaseCharacter();
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	bool IsAlive() { return bAlive; };
	void SetAlive(bool bAliveStatus) { bAlive = bAliveStatus; };

private:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive = true;
};
