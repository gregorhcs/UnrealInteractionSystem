// Copyright 2024 Thieves of the Night. All Rights Reserved.

// ReSharper disable CppUEBlueprintCallableFunctionUnused

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameplayAbilities/Public/Abilities/GameplayAbility.h"

#include "AbilityInteract.generated.h"

class UInteractableLocator;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_AbilityInteract);

/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API UAbilityInteract : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UAbilityInteract();

	// - UAbility
	virtual bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags,
		const FGameplayTagContainer* TargetTags,
		FGameplayTagContainer* OptionalRelevantTags
	) const override;
	virtual void InputReleased(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo
	) override;
	// --

protected:
	// - UAbility
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled
	) override;
	// --

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartInteract(UInteractableComponent* Interactable);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReleaseInteract(UInteractableComponent* Interactable);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndInteract(UInteractableComponent* Interactable);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UInteractableLocator> InteractableLocator;

	UPROPERTY(EditDefaultsOnly)
	bool bEndRightAfterStart = false;
};
