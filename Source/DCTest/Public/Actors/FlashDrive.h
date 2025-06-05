// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlashDrive.generated.h"

class UPaperSprite;
class UDraggableSpriteComponent;
class AFlashDriveUnlockGame;

#define ECC_Ground ECC_GameTraceChannel1

/**
 * 
 */
UCLASS()
class DCTEST_API AFlashDrive : public AActor
{
	GENERATED_BODY()
	
public:
	AFlashDrive();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDraggableSpriteComponent> BodySprite;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFlashDriveUnlockGame> UnlockGameClass;

	UPROPERTY(EditAnywhere)
	FVector UnlockGameLocation = FVector(0, 10, 0);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSprite> LockedSprite;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSprite> UnlockedSprite;

protected:
	bool bIsLocked = true;
	TObjectPtr<AFlashDriveUnlockGame> UnlockGame;

protected:
	virtual void BeginPlay() override;

public:
	void StartFalling();

protected:
	UFUNCTION(BlueprintCallable)
	void StartUnlockGame();

	UFUNCTION(BlueprintCallable)
	void Unlock();

	UFUNCTION()
	void OnHitSurface(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
