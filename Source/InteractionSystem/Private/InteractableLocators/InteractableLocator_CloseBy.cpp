// Copyright 2024 Thieves of the Night. All Rights Reserved.


#include "InteractableLocators/InteractableLocator_CloseBy.h"

#define ECC_Trigger ECC_GameTraceChannel2

UInteractableComponent* UInteractableLocator_CloseBy::FindInteractable_Implementation(UWorld* World, const AActor* Interactor)
{
	TArray<FHitResult> Hits;
	SweepEnvironment(World, Interactor, Hits);

	const FHitResult* ClosestInteractableHit = Algo::MinElementBy(
		Hits,
		[&Interactor](const FHitResult& HitResult)
		{
			const AActor* HitActor = HitResult.GetActor();
			if (!IsValid(HitActor))
				return TNumericLimits<float>::Max();

			const auto Interactable = HitActor->GetComponentByClass<UInteractableComponent>();
			if (!IsValid(Interactable))
				return TNumericLimits<float>::Max();

			return StaticCast<float>(FVector::DistSquared(HitActor->GetActorLocation(), Interactor->GetActorLocation()));
		});

	if (!ClosestInteractableHit)
		return nullptr;

	return ClosestInteractableHit->GetActor()->GetComponentByClass<UInteractableComponent>();
}

void UInteractableLocator_CloseBy::SweepEnvironment(
	const UWorld* World,
	const AActor* Interactor,
	TArray<FHitResult>& OutHitResults) const
{
	const FVector InteractorLocation = Interactor->GetActorLocation();
	const FVector InteractorForward = Interactor->GetActorForwardVector();

	const FVector Start = InteractorLocation + InteractorForward * StartForwardOffset;
	const FVector End   = InteractorLocation + InteractorForward * EndForwardOffset;

	if (bDrawDebugSphere)
	{
		DrawDebugSphere(World, Start, SweepSphereSize, 10, FColor::Red, true);
		DrawDebugSphere(World, End,   SweepSphereSize, 10, FColor::Red, true);

		DrawDebugLine(World, Start + FVector::UpVector * SweepSphereSize / 2, End + FVector::UpVector * SweepSphereSize / 2, FColor::Red, true);
		DrawDebugLine(World, Start - FVector::UpVector * SweepSphereSize / 2, End - FVector::UpVector * SweepSphereSize / 2, FColor::Red, true);
		DrawDebugLine(World, Start + FVector::RightVector * SweepSphereSize / 2, End + FVector::RightVector * SweepSphereSize / 2, FColor::Red, true);
		DrawDebugLine(World, Start - FVector::RightVector * SweepSphereSize / 2, End - FVector::RightVector * SweepSphereSize / 2, FColor::Red, true);
	}
	
	World->SweepMultiByChannel(
		OutHitResults,
		Start, End,
		FQuat::Identity,
		ECC_Trigger,
		FCollisionShape::MakeSphere(SweepSphereSize));
}
