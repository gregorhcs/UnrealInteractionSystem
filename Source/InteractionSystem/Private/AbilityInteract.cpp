// Copyright 2024 Gregor Sönnichsen. All Rights Reserved.


#include "AbilityInteract.h"

#include "InteractableLocator.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_AbilityInteract, "Ability.Interact");

UAbilityInteract::UAbilityInteract()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationOwnedTags.AddTag(TAG_AbilityInteract);
}

bool UAbilityInteract::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags
) const
{
	if (!ensureMsgf(InteractableLocator, TEXT("No InteractableLocator was assigned or saved into the AbilityInteract!")))
		return false;
	
	if (ActorInfo->AvatarActor.IsStale())
		return false;

	const AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	UWorld* World = ActorInfo->OwnerActor.Get()->GetWorld();
	
	UInteractableComponent* Interactable = InteractableLocator->FindAndCacheInteractable(World, AvatarActor);

	if (!IsValid(Interactable))
		return false;

	const bool bInteractionClassMatches = Interactable->AllowsInteraction(GetClass());
	
	return bInteractionClassMatches;
}

void UAbilityInteract::InputReleased(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
	UInteractableComponent* Interactee = InteractableLocator->GetPreviouslyFoundInteractable();
	
	// Call virtual functions for interaction release
	ReleaseInteract(InteractableLocator->GetPreviouslyFoundInteractable());
	Interactee->ReleaseInteractedWith(ActorInfo->AvatarActor.Get());
	// --
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UAbilityInteract::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	UInteractableComponent* Interactee = InteractableLocator->GetPreviouslyFoundInteractable();

	// Call virtual functions for interaction start
	StartInteract(Interactee);
	Interactee->StartInteractedWith(ActorInfo->AvatarActor.Get());
	// --

	if (bEndRightAfterStart)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

void UAbilityInteract::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UInteractableComponent* Interactee = InteractableLocator->GetPreviouslyFoundInteractable();
	
	// Call virtual functions for interaction release
	EndInteract(InteractableLocator->GetPreviouslyFoundInteractable());
	Interactee->EndInteractedWith(ActorInfo->AvatarActor.Get());
	// --
}

void UAbilityInteract::StartInteract_Implementation(UInteractableComponent* Interactable)
{
}

void UAbilityInteract::ReleaseInteract_Implementation(UInteractableComponent* Interactable)
{
}

void UAbilityInteract::EndInteract_Implementation(UInteractableComponent* Interactable)
{
}
