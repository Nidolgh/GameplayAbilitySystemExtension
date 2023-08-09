#include "GASActor.h"

#include "BaseAbilitySystemComponent.h"

AGASActor::AGASActor()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
}

UAbilitySystemComponent* AGASActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
