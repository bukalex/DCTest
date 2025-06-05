// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FlashDrive.h"

#include "Components/DraggableSpriteComponent.h"
#include "Actors/FlashDriveUnlockGame.h"

AFlashDrive::AFlashDrive()
{
	PrimaryActorTick.bCanEverTick = false;

	BodySprite = CreateDefaultSubobject<UDraggableSpriteComponent>("BodySprite");
	SetRootComponent(BodySprite);
}

void AFlashDrive::BeginPlay()
{
	Super::BeginPlay();

	BodySprite->OnSpriteClicked.AddDynamic(this, &AFlashDrive::StartUnlockGame);
	BodySprite->SetSprite(bIsLocked ? LockedSprite : UnlockedSprite);
}

void AFlashDrive::StartUnlockGame()
{
	if (!bIsLocked) return;
	if (!UnlockGameClass) return;
	if (UnlockGame) return;

	UnlockGame = GetWorld()->SpawnActor<AFlashDriveUnlockGame>(UnlockGameClass, UnlockGameLocation, FRotator());
	UnlockGame->OnDriveUnlocked.AddDynamic(this, &AFlashDrive::Unlock);
}

void AFlashDrive::Unlock()
{
	bIsLocked = false;
	BodySprite->SetSprite(UnlockedSprite);
}