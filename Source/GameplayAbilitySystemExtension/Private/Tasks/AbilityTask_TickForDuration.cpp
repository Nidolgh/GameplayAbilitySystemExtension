#include "Tasks/AbilityTask_TickForDuration.h"

UAbilityTask_TickForDuration::UAbilityTask_TickForDuration()
{
	bTickingTask = true;
	
}

UAbilityTask_TickForDuration* UAbilityTask_TickForDuration::TickForDuration(UGameplayAbility* OwningAbility,
	FName TaskInstanceName, float Duration)
{
	UAbilityTask_TickForDuration* MyObj = NewAbilityTask<UAbilityTask_TickForDuration>(OwningAbility, TaskInstanceName);

	MyObj->TimeStarted = MyObj->GetWorld()->GetTimeSeconds();
	MyObj->TimeWillEnd = MyObj->TimeStarted + Duration;

	return MyObj;
}

void UAbilityTask_TickForDuration::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (GetWorld()->GetTimeSeconds() >= TimeWillEnd)
	{
		OnEnd.Broadcast(TimeStarted, TimeWillEnd, TimeWillEnd - GetWorld()->GetTimeSeconds());
		EndTask();
	}
	else
	{
		OnTick.Broadcast(TimeStarted, TimeWillEnd, TimeWillEnd - GetWorld()->GetTimeSeconds());
	}
}