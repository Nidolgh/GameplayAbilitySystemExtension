// Fill out your copyright notice in the Description page of Project Settings.

#include "GASPawn.h"

#include "BaseAbilitySystemComponent.h"

// Sets default values
AGASPawn::AGASPawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
}

void AGASPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (AbilitySystemComponent == nullptr)
	{
		return;
	}
	
	AbilitySystemComponent->BindToInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AGASPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
