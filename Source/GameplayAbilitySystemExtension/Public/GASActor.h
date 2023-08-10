#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GASActor.generated.h"

/** 
 * GASActor is the base class of all actors that should make use of the Gameplay Ability System (GAS)
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEPLAYABILITYSYSTEMEXTENSION_API AGASActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actors properties
	AGASActor();
	
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// End
	
	UPROPERTY(Category="Gameplay Ability System", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UBaseAbilitySystemComponent* AbilitySystemComponent;
};