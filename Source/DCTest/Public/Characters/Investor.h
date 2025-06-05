// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Investor.generated.h"

class UCameraComponent;

/**
 * 
 */
UCLASS()
class DCTEST_API AInvestor : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	AInvestor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;
};
