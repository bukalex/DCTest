// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Founder.generated.h"

class AFlashDrive;

/**
 * 
 */
UCLASS()
class DCTEST_API AFounder : public APaperCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFlashDrive> FlashDriveClass;

	UPROPERTY(EditAnywhere)
	float DriveYOrder = 2;

protected:
	TObjectPtr<AFlashDrive> FlashDrive;
	bool bIsMoving = false;
	FVector Destination;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void GoToLocation(const FVector& Location);

protected:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
