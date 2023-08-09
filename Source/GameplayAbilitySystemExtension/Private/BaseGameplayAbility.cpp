// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"

#include "AbilitySystemComponent.h"

UBaseGameplayAbility::UBaseGameplayAbility()
	: bActivateOnGranted(false)
{
	
}

void UBaseGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
