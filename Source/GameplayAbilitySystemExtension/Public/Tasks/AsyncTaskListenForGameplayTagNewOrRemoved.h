// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskListenForGameplayTagNewOrRemoved.generated.h"

struct FActiveGameplayEffectHandle;

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayTagChanged, const FGameplayTag, Tag, int32, NewCount);

/**
 * 
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncTask))
class GAMEPLAYABILITYSYSTEMEXTENSION_API UAsyncTaskListenForGameplayTagNewOrRemoved : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameplayTagChanged OnGameplayTagAdded;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayTagChanged OnGameplayTagRemoved;
	
	// Listens for changes (Begin and End) to cooldown GameplayEffects based on the cooldown tag.
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskListenForGameplayTagNewOrRemoved* ListenForGameplayTagNewOrRemoved(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InTagToListenFor, bool bUseExactMatch);

	// You must call this function manually when you want the AsyncTask to end.
	// For UMG Widgets, you would call it in the Widget's Destruct event.
	UFUNCTION(BlueprintCallable)
	void EndTask();
	
	void OnGameplayTagChangedCallback(const FGameplayTag, int32) const;

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayTag TagToListenFor;

	TArray<FDelegateHandle> DelegateHandles;

	bool bUseExact;
};
