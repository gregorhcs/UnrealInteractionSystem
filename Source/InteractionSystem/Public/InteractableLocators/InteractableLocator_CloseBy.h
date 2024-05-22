// Copyright 2024 Thieves of the Night. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableLocator.h"
#include "InteractableLocator_CloseBy.generated.h"

/**
 * Searches for an interactable in the surrounding of the interactor.
 */
UCLASS()
class INTERACTIONSYSTEM_API UInteractableLocator_CloseBy : public UInteractableLocator
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	virtual UInteractableComponent* FindInteractable_Implementation(UWorld* World, const AActor* Interactor) override;

	UPROPERTY(EditDefaultsOnly, Category="LEnvironment Sweep")
	float StartForwardOffset = 50.f;

	UPROPERTY(EditDefaultsOnly, Category="Environment Sweep")
	float EndForwardOffset = 70.f;

	UPROPERTY(EditDefaultsOnly, Category="Environment Sweep")
	float SweepSphereSize = 70.f;

	UPROPERTY(EditDefaultsOnly, Category="Debug")
	bool bDrawDebugSphere = false;

	void SweepEnvironment(const UWorld* World, const AActor* Interactor, TArray<FHitResult>& OutHitResults) const;
};
