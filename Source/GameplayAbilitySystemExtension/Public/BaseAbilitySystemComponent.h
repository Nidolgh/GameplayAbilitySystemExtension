// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITYSYSTEMEXTENSION_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BindToInputComponent(UInputComponent* InputComponent) override;
	
protected:
	UPROPERTY()
	const class UBaseAttributeSet* BaseAttributeSet;

	// Adds loose gameplay tags at start which are not backed by a GameplayEffect
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	FGameplayTagContainer StartupGameplayTags;

	// list of default gameplay abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class UBaseGameplayAbility>> CharacterAbilities;

	// The set of attributes we will initialize
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UAttributeSet> DefaultAttributeSet;
	
	// Effect that initializes our default attribute set
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS", meta = (EditCondition = "DefaultAttributeSet != nullptr"))
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
	
	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

private:
	void InitializeAttributes();
	void AddStartupEffects();
	void GiveAbilities();

	bool bAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	UEnhancedInputComponent* OwningInputComponent = nullptr;
};
