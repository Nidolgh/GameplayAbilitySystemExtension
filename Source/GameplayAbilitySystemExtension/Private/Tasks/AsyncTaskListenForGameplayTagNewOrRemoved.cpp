// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/AsyncTaskListenForGameplayTagNewOrRemoved.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"

UAsyncTaskListenForGameplayTagNewOrRemoved* UAsyncTaskListenForGameplayTagNewOrRemoved::ListenForGameplayTagNewOrRemoved(
	UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InTagToListenFor, bool bUseExactMatch)
{
	UAsyncTaskListenForGameplayTagNewOrRemoved* ListenForGameplayTagChange = NewObject<UAsyncTaskListenForGameplayTagNewOrRemoved>();
	ListenForGameplayTagChange->ASC = AbilitySystemComponent;
	ListenForGameplayTagChange->TagToListenFor = InTagToListenFor;
	ListenForGameplayTagChange->bUseExact = bUseExactMatch;

	if (!IsValid(AbilitySystemComponent))
	{
		ListenForGameplayTagChange->EndTask();
		return nullptr;
	}

	TArray<FGameplayTag> TagArray;

	if (bUseExactMatch)
	{
		TagArray.Add(InTagToListenFor);
	}
	else
	{
		const FGameplayTagContainer DirectChildTagContainer = UGameplayTagsManager::Get().RequestGameplayTagChildren(InTagToListenFor);
		DirectChildTagContainer.GetGameplayTagArray(TagArray);
	}

	for (const FGameplayTag& Tag : TagArray)
	{
		ListenForGameplayTagChange->DelegateHandles.Add(AbilitySystemComponent->RegisterGameplayTagEvent(Tag).AddUObject(ListenForGameplayTagChange, &UAsyncTaskListenForGameplayTagNewOrRemoved::OnGameplayTagChangedCallback));
	}

	return ListenForGameplayTagChange;
}

void UAsyncTaskListenForGameplayTagNewOrRemoved::EndTask()
{
	if(IsValid(ASC))
	{
		for	(const FDelegateHandle DelegateHandle : DelegateHandles)
		{
			ASC->UnregisterGameplayTagEvent(DelegateHandle, TagToListenFor);
		}
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAsyncTaskListenForGameplayTagNewOrRemoved::OnGameplayTagChangedCallback(const FGameplayTag Tag, int32 NewCount) const
{
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		OnGameplayTagAdded.Broadcast(Tag, NewCount);
	}
	else
	{
		OnGameplayTagRemoved.Broadcast(Tag, NewCount);
	}
}
