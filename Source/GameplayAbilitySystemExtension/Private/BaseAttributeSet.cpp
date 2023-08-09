// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAttributeSet.h"

#include "GameplayEffectExtension.h"

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHitpointsAttribute())
	{
		SetHitpoints(FMath::Clamp(GetHitpoints(), 0.f, 100.f));
	}
}