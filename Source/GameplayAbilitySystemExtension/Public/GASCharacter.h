﻿#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "GASCharacter.generated.h"

UCLASS()
class GAMEPLAYABILITYSYSTEMEXTENSION_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASCharacter();
	
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	UPROPERTY(Category="Gameplay Ability System", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UBaseAbilitySystemComponent* AbilitySystemComponent;
};
