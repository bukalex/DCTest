// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DraggableSpriteComponent.h"

UDraggableSpriteComponent::UDraggableSpriteComponent()
{
	SetSimulatePhysics(false);
}

void UDraggableSpriteComponent::StartDragging(const FVector& MousePosition)
{
	FVector MouseHitPosition = MousePosition;
	ZeroDepth(MouseHitPosition);

	LastMouseHitPosition = MouseHitPosition;
}

bool UDraggableSpriteComponent::DragTo(const FVector& NewMousePosition)
{
	FVector ZeroItterationPosition = LastMouseHitPosition;
	FVector MouseHitPosition = NewMousePosition;
	ZeroDepth(MouseHitPosition);

	if ((MouseHitPosition - LastMouseHitPosition).IsNearlyZero()) return false;

	int32 Itteration = 1;
	while (Itteration <= Itterations)
	{
		FVector ItteratedHitPosition = FMath::Lerp(ZeroItterationPosition, MouseHitPosition, ((float)Itteration) / Itterations);

		TObjectPtr<USceneComponent> AffectedComponent = bDragWithRoot ? GetOwner()->GetRootComponent() : this;

		FVector Translation = ItteratedHitPosition - LastMouseHitPosition;
		FVector OldPosition = AffectedComponent->GetComponentLocation();
		ZeroDepth(OldPosition);

		if (!bLockTranslation) AffectedComponent->AddWorldOffset(Translation, true);

		FVector NewPosition = AffectedComponent->GetComponentLocation();
		ZeroDepth(NewPosition);

		if (!bLockRotation)
		{
			FVector MouseToOldPosition = OldPosition - ItteratedHitPosition;
			FVector MouseToNewPosition = NewPosition - ItteratedHitPosition;

			FQuat DeltaQuat = FQuat::FindBetweenVectors(MouseToNewPosition, MouseToOldPosition);
			AffectedComponent->AddWorldRotation(DeltaQuat, true);

			if (!bLockTranslation)
			{
				FVector RotationCorrection = -MouseToNewPosition + MouseToOldPosition.GetSafeNormal() * MouseToNewPosition.Size();
				AffectedComponent->AddWorldOffset(RotationCorrection, true);
			}
		}

		LastMouseHitPosition = ItteratedHitPosition;
		Itteration++;
	}

	return true;
}

void UDraggableSpriteComponent::ZeroDepth(FVector& Vector)
{
	Vector = FVector::VectorPlaneProject(Vector, GetRightVector());
}

void UDraggableSpriteComponent::Click()
{
	OnSpriteClicked.Broadcast();
}