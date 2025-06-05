// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "USBPortComponent.generated.h"

class AFlashDrive;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlashDriveEvent, const AFlashDrive*, FlashDrive);

/**
 * 
 */
UCLASS()
class DCTEST_API UUSBPortComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnFlashDriveEvent OnFlashDriveDetected;

	UPROPERTY(BlueprintAssignable)
	FOnFlashDriveEvent OnFlashDriveLost;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AFlashDrive> InsertedDrive;

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnDriveBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDriveEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
