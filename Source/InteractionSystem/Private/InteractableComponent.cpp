// Copyright 2024 Thieves of the Night. All Rights Reserved.


#include "InteractableComponent.h"

#include "Algo/AnyOf.h"

void UInteractableComponent::StartInteractedWith_Implementation(AActor* Interactor)
{
	OnInteractionStarted.Broadcast(this, Interactor);
}

void UInteractableComponent::ReleaseInteractedWith_Implementation(AActor* Interactor)
{
	OnInteractionReleased.Broadcast(this, Interactor);
}

void UInteractableComponent::EndInteractedWith_Implementation(AActor* Interactor)
{
	OnInteractionEnded.Broadcast(this, Interactor);
}

bool UInteractableComponent::AllowsInteraction(TSubclassOf<UAbilityInteract> TestedInteractionClass)
{
	return Algo::AnyOf(AllowedInteractions, [&](auto InteractionClass)
	{
		return TestedInteractionClass->IsChildOf(*InteractionClass);
	});
}
