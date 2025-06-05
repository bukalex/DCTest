// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "DraggableSpriteComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpriteClicked);

/**
 * 
 */
UCLASS()
class DCTEST_API UDraggableSpriteComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	UDraggableSpriteComponent();

public:
	UPROPERTY(BlueprintAssignable)
	FOnSpriteClicked OnSpriteClicked;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag And Drop")
	bool bLockTranslation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag And Drop")
	bool bLockRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag And Drop")
	bool bDragWithRoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag And Drop")
	int32 Itterations = 4;

protected:
	FVector LastMouseHitPosition;

public:
	void StartDragging(const FVector& MousePosition);
	bool DragTo(const FVector& NewMousePosition);

	void Click();

protected:
	void ZeroDepth(FVector& Vector);
};
