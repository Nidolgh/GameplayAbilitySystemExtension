#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TickForDuration.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTickForDurationDelegate, float, TimeStarted, float, TimeWillEnd, float, TimeLeft);
/**
 * 
 */
UCLASS()
class GAMEPLAYABILITYSYSTEMEXTENSION_API UAbilityTask_TickForDuration : public UAbilityTask
{
	GENERATED_BODY()

	UAbilityTask_TickForDuration();

	UPROPERTY(BlueprintAssignable)
	FTickForDurationDelegate OnTick;

	UPROPERTY(BlueprintAssignable)
	FTickForDurationDelegate OnEnd;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_TickForDuration* TickForDuration(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration);

	/** Tick function for this task, if bTickingTask == true */
	virtual void TickTask(float DeltaTime) override;

protected:
	float Duration;
	float TimeStarted;
	float TimeWillEnd;
};
