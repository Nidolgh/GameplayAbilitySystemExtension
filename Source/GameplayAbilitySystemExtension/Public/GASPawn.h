// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Pawn.h"
#include "GASPawn.generated.h"

/** 
 * GASPawn is the base class of all actors that should make use of the Gameplay Ability System (GAS), can be possessed by players or AI .
 */
UCLASS()
class GAMEPLAYABILITYSYSTEMEXTENSION_API AGASPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGASPawn();
	
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category="Gameplay Ability System", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UBaseAbilitySystemComponent* AbilitySystemComponent;
};
