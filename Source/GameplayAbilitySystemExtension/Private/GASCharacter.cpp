// Fill out your copyright notice in the Description page of Project Settings.

#include "GASCharacter.h"

#include "BaseAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGASCharacter::AGASCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
}

void AGASCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (AbilitySystemComponent == nullptr)
	{
		return;	
	}
	
	const FString PreFix = "State.MovementMode.";
	
	FString Result = PreFix + UEnum::GetDisplayValueAsText(GetCharacterMovement()->MovementMode).ToString();
	AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName(Result), false));

	Result = PreFix + UEnum::GetDisplayValueAsText(PrevMovementMode).ToString();
	AbilitySystemComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName(Result), false));
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


