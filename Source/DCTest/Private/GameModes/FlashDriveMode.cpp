// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/FlashDriveMode.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/Founder.h"

void AFlashDriveMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFounder::StaticClass(), WaitingFounders);
}

void AFlashDriveMode::CallNextFounder()
{
	if (!bCanCallNextFounder) return;

	if (IsValid(CurrentFounder)) CurrentFounder->GoToLocation(ExitLocation);
	if (WaitingFounders.Num() <= 0) return;

	CurrentFounder = Cast<AFounder>(WaitingFounders[FMath::Rand() % WaitingFounders.Num()]);
	WaitingFounders.Remove(CurrentFounder);

	if (IsValid(CurrentFounder))
	{
		CurrentFounder->GoToLocation(TableLocation);
		bCanCallNextFounder = false;
	}
	else CallNextFounder();
}