#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "GASCharacter.generated.h"

UCLASS()
class GAMEPLAYABILITYSYSTEMEXTENSION_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASCharacter();

protected:
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	
public:
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="GAS")
	class UBaseAbilitySystemComponent* AbilitySystemComponent;
};
