// Copyright 2024 Thieves of the Night. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "UObject/Object.h"
#include "InteractableLocator.generated.h"

struct FGameplayTag;

/**
 * 
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class INTERACTIONSYSTEM_API UInteractableLocator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UInteractableComponent* FindAndCacheInteractable(UWorld* World, const AActor* Interactor);

	UFUNCTION(BlueprintCallable)
	UInteractableComponent* GetPreviouslyFoundInteractable() const;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UInteractableComponent* FindInteractable(UWorld* World, const AActor* Interactor);
	
	UPROPERTY(Transient)
	TObjectPtr<UInteractableComponent> PreviouslyFoundInteractable = nullptr;
};
