// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "FlashDriveUnlockGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDriveUnlocked);

/**
 * 
 */
UCLASS()
class DCTEST_API AFlashDriveUnlockGame : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	AFlashDriveUnlockGame();

public:
	UPROPERTY(BlueprintAssignable)
	FOnDriveUnlocked OnDriveUnlocked;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FComponentReference ScaledComponentReference;

	UPROPERTY(EditAnywhere)
	FVector TargetScale = FVector(1.5f, 1.5f, 1.5f);

	UPROPERTY(EditAnywhere)
	float ScalingSpeed = 5;

protected:
	TObjectPtr<USceneComponent> ScaledComponent;
	FVector InitialScale = FVector(1, 1, 1);

	bool bIsGrowing = true;
	bool bIsLocked = true;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	void UnlockDrive();
};
