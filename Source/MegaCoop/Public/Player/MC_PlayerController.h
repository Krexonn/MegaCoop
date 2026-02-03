// Copyright Krexonn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class MEGACOOP_API AMC_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
private:

	UPROPERTY(EditDefaultsOnly, Category = "MegaC|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "MegaC|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "MegaC|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "MegaC|Input|Movement")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "MegaC|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;

	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Primary();
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
	bool IsAlive() const;
};
