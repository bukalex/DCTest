// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DraggableSpriteComponent.h"

UDraggableSpriteComponent::UDraggableSpriteComponent()
{
	SetSimulatePhysics(true);
	SetEnableGravity(false);

	BodyInstance.bLockXRotation = true;
	BodyInstance.bLockYRotation = false;
	BodyInstance.bLockZRotation = true;

	BodyInstance.bLockXTranslation = false;
	BodyInstance.bLockYTranslation = true;
	BodyInstance.bLockZTranslation = false;
}

void UDraggableSpriteComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AffectedComponentReference.ComponentProperty.IsNone() || !AffectedComponentReference.GetComponent(GetOwner()))
	{
		AffectedComponent = this;
	}
	else if (USceneComponent* Component = Cast<USceneComponent>(AffectedComponentReference.GetComponent(GetOwner())))
	{
		AffectedComponent = Component;
	}
	else
	{
		AffectedComponent = this;
	}
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

	if (!AffectedComponent) AffectedComponent = this;
	int32 Itteration = 1;

	while (Itteration <= Itterations)
	{
		FVector ItteratedHitPosition = FMath::Lerp(ZeroItterationPosition, MouseHitPosition, ((float)Itteration) / Itterations);

		FVector Translation = ItteratedHitPosition - LastMouseHitPosition;
		FVector NewPosition;
		FVector OldPosition = AffectedComponent->GetComponentLocation();
		ZeroDepth(OldPosition);

		if (!bLockTranslation)
		{
			AffectedComponent->AddWorldOffset(Translation, true);
			NewPosition = AffectedComponent->GetComponentLocation();
		}
		else
		{
			NewPosition = OldPosition + Translation;
		}
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

	OnSpriteMoved.Broadcast();

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