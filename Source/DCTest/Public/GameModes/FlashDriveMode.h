// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlashDriveMode.generated.h"

class AFounder;

/**
 * 
 */
UCLASS()
class DCTEST_API AFlashDriveMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	FVector ExitLocation;

	UPROPERTY(EditAnywhere)
	FVector TableLocation;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bCanCallNextFounder = true;

protected:
	TArray<TObjectPtr<AActor>> WaitingFounders;
	TObjectPtr<AFounder> CurrentFounder;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void CallNextFounder();
};
