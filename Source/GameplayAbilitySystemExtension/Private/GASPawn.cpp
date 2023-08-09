// Fill out your copyright notice in the Description page of Project Settings.

#include "GASPawn.h"

#include "BaseAbilitySystemComponent.h"

// Sets default values
AGASPawn::AGASPawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
}

UAbilitySystemComponent* AGASPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}