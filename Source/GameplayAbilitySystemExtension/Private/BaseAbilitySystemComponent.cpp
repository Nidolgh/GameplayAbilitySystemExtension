// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilitySystemComponent.h"

#include "BaseGameplayAbility.h"
#include "BaseAttributeSet.h"
#include "EnhancedInputComponent.h"

void UBaseAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	BaseAttributeSet = GetSet<UBaseAttributeSet>();
	AddLooseGameplayTags(StartupGameplayTags);

	InitAbilityActorInfo(GetOwner(), GetOwner());

	InitializeAttributes();
	AddStartupEffects();
	GiveAbilities();
}

void UBaseAbilitySystemComponent::BindToInputComponent(UInputComponent* InputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	OwningInputComponent = EnhancedInputComponent;
}

void UBaseAbilitySystemComponent::InitializeAttributes()
{
	if (!IsValid(DefaultAttributes))
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UBaseAbilitySystemComponent::AddStartupEffects()
{
	if (!bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(GameplayEffect, 1.0f, EffectContext);
		if (NewHandle.IsValid())
		{
			ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), this);
		}
	}
	
	bStartupEffectsApplied = true;
}

void UBaseAbilitySystemComponent::GiveAbilities()
{
	if (bAbilitiesGiven)
	{
		return;
	}
	
	// Grant abilities
	for (TSubclassOf<UBaseGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		if (IsValid(StartupAbility))
		{
			int32 InputID = INDEX_NONE;

			const UInputAction* InpAction = StartupAbility.GetDefaultObject()->InputAction;
			if (OwningInputComponent != nullptr && InpAction != nullptr)
			{
				InputID = InpAction->GetUniqueID();
				
				const FEnhancedInputActionHandlerSignature::TMethodPtr<UAbilitySystemComponent, int> PressedDelegate = &UAbilitySystemComponent::AbilityLocalInputPressed;
				OwningInputComponent->BindAction(InpAction, ETriggerEvent::Started, this, PressedDelegate, InputID);

				const FEnhancedInputActionHandlerSignature::TMethodPtr<UAbilitySystemComponent, int> ReleasedDelegate = &UAbilitySystemComponent::AbilityLocalInputReleased;
				OwningInputComponent->BindAction(InpAction, ETriggerEvent::Completed, this, ReleasedDelegate, InputID);
			}
			
			GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, InputID, this));
		}
	}

	bAbilitiesGiven = true;
}
