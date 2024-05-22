// Copyright 2024 Thieves of the Night. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityInteract.h"
#include "InteractableComponent.generated.h"

class UInteractableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractedWithDelegate, UInteractableComponent*, Interactee, AActor*, Interactor);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartInteractedWith(AActor* Interactor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReleaseInteractedWith(AActor* Interactor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndInteractedWith(AActor* Interactor);
	
	UFUNCTION(BlueprintCallable)
	bool AllowsInteraction(TSubclassOf<UAbilityInteract> InteractionClass);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UAbilityInteract>> AllowedInteractions;

	UPROPERTY(BlueprintAssignable)
	FOnInteractedWithDelegate OnInteractionStarted;
	UPROPERTY(BlueprintAssignable)
	FOnInteractedWithDelegate OnInteractionReleased;
	UPROPERTY(BlueprintAssignable)
	FOnInteractedWithDelegate OnInteractionEnded;
};
