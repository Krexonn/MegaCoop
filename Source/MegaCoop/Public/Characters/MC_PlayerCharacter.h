// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "MC_BaseCharacter.h"
#include "MC_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MEGACOOP_API AMC_PlayerCharacter : public AMC_BaseCharacter
{
	GENERATED_BODY()

public:
	
	AMC_PlayerCharacter();
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
