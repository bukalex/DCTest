// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laptop.generated.h"

class UPaperSpriteComponent;
class UUSBPortComponent;
class AFlashDrive;

UCLASS()
class DCTEST_API ALaptop : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaptop();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPaperSpriteComponent> BodySprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UUSBPortComponent> USBPort;

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnDriveDetected(const AFlashDrive* FlashDrive);

	UFUNCTION()
	void OnDriveLost(const AFlashDrive* FlashDrive);
};
