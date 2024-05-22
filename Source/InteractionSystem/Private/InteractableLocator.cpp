// Copyright 2024 Thieves of the Night. All Rights Reserved.


#include "InteractableLocator.h"

UInteractableComponent* UInteractableLocator::FindAndCacheInteractable(UWorld* World, const AActor* Interactor)
{
	UInteractableComponent* NewInteractable = FindInteractable(World, Interactor);

	if (!IsValid(NewInteractable))
		return nullptr;

	PreviouslyFoundInteractable = NewInteractable;
	return NewInteractable;
}

UInteractableComponent* UInteractableLocator::FindInteractable_Implementation(UWorld* World, const AActor* Interactor)
{
	return nullptr;
}

UInteractableComponent* UInteractableLocator::GetPreviouslyFoundInteractable() const
{
	return PreviouslyFoundInteractable;
}
