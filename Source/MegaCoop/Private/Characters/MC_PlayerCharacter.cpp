// Copyright Krexonn


#include "Characters/MC_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MC_AttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMC_PlayerCharacter::AMC_PlayerCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement= true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	CameraBoom = CreateOptionalDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateOptionalDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* AMC_PlayerCharacter::GetAbilitySystemComponent() const
{
	AMC_PlayerState* MCPlayerState = Cast<AMC_PlayerState>(GetPlayerState());
	if (!MCPlayerState) return nullptr;

	return MCPlayerState->GetAbilitySystemComponent();
}

UAttributeSet* AMC_PlayerCharacter::GetAttributeSet() const
{
	AMC_PlayerState* MCPlayerState = Cast<AMC_PlayerState>(GetPlayerState());
	if (!IsValid(MCPlayerState)) return nullptr;

	return MCPlayerState->GetAttributeSet();
}

void AMC_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!IsValid(GetAbilitySystemComponent())|| !HasAuthority()) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes();
	
	UMC_AttributeSet* MC_AttributeSet = Cast<UMC_AttributeSet>(GetAttributeSet());
	if (!IsValid(MC_AttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(MC_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void AMC_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	UMC_AttributeSet* MC_AttributeSet = Cast<UMC_AttributeSet>(GetAttributeSet());
	if (!IsValid(MC_AttributeSet)) return;

	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(MC_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}


