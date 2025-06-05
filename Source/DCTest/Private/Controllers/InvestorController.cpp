// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/InvestorController.h"

#include "Characters/Investor.h"
#include "Components/DraggableSpriteComponent.h"

void AInvestorController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(ActionMapping, 0);

		if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
		{
			Input->BindAction(DragAction, ETriggerEvent::Started, this, &AInvestorController::DragStart);
			Input->BindAction(DragAction, ETriggerEvent::Triggered, this, &AInvestorController::Drag);
			Input->BindAction(DragAction, ETriggerEvent::Completed, this, &AInvestorController::Drop);
		}
	}

	SetShowMouseCursor(true);
}

void AInvestorController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (AInvestor* Investor = Cast<AInvestor>(aPawn))
	{
		ControlledInvestor = Investor;
	}
}

bool AInvestorController::LineTraceFromMouse(FHitResult& HitResult)
{
	FVector MouseLocation;
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	const FVector Start = MouseLocation;
	const FVector End = Start + MouseDirection * LineTraceDepth;
	ECollisionChannel TraceChannel = ECC_Visibility;

	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
}

void AInvestorController::DragStart()
{
	FHitResult HitResult;
	if (LineTraceFromMouse(HitResult))
	{
		if (UDraggableSpriteComponent* DraggableComponent = Cast<UDraggableSpriteComponent>(HitResult.GetComponent()))
		{
			bStartedDragging = false;
			DraggedSprite = DraggableComponent;
			DraggedSprite->StartDragging(HitResult.ImpactPoint);
		}
	}
}

void AInvestorController::Drag()
{
	if (!DraggedSprite) return;

	FHitResult HitResult;
	if (LineTraceFromMouse(HitResult))
	{
		if (UDraggableSpriteComponent* DraggableComponent = Cast<UDraggableSpriteComponent>(HitResult.GetComponent()))
		{
			if (DraggableComponent == DraggedSprite)
			{
				if (DraggedSprite->DragTo(HitResult.ImpactPoint))
				{
					bStartedDragging = true;
				}
			}
			else
			{
				Drop();
			}
		}
	}
	else
	{
		Drop();
	}
}

void AInvestorController::Drop()
{
	if (!DraggedSprite) return;

	if (!bStartedDragging)
	{
		DraggedSprite->Click();
	}

	DraggedSprite = nullptr;
	bStartedDragging = false;
}