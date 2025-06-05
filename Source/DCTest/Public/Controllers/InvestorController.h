// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InvestorController.generated.h"

class AInvestor;
class UDraggableSpriteComponent;

/**
 * 
 */
UCLASS()
class DCTEST_API AInvestorController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputMappingContext> ActionMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	TObjectPtr<UInputAction> DragAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	float LineTraceDepth = 1000;

protected:
	TObjectPtr<AInvestor> ControlledInvestor;
	TObjectPtr<UDraggableSpriteComponent> DraggedSprite;

	bool bStartedDragging = false;

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

protected:
	bool LineTraceFromMouse(FHitResult& HitResult);

	void DragStart();
	void Drag();
	void Drop();
};
