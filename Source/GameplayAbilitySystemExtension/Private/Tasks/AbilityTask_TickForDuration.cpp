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
	MyObj->TimeWillEnd = Duration <= 0.0f ? 0.0f : MyObj->TimeStarted + Duration;
	
	return MyObj;
}

void UAbilityTask_TickForDuration::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	if (TimeWillEnd > 0.0f && GetWorld()->GetTimeSeconds() >= TimeWillEnd)
	{
		OnEnd.Broadcast(TimeStarted, TimeWillEnd, TimeWillEnd - GetWorld()->GetTimeSeconds());
		EndTask();
	}
	else
	{
		OnTick.Broadcast(TimeStarted, TimeWillEnd, TimeWillEnd - GetWorld()->GetTimeSeconds());
	}
}