// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Laptop.h"

#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"
#include "Components/USBPortComponent.h"
#include "GameModes/FlashDriveMode.h"

ALaptop::ALaptop()
{
	PrimaryActorTick.bCanEverTick = false;

	BodySprite = CreateDefaultSubobject<UPaperSpriteComponent>("BodySprite");
	SetRootComponent(BodySprite);

	USBPort = CreateDefaultSubobject<UUSBPortComponent>("USBSprite");
	USBPort->SetupAttachment(GetRootComponent());
}

void ALaptop::BeginPlay()
{
	Super::BeginPlay();

	USBPort->OnFlashDriveDetected.AddDynamic(this, &ALaptop::OnDriveDetected);
	USBPort->OnFlashDriveLost.AddDynamic(this, &ALaptop::OnDriveLost);
}

void ALaptop::OnDriveDetected(const AFlashDrive* FlashDrive)
{

}

void ALaptop::OnDriveLost(const AFlashDrive* FlashDrive)
{
	if (AFlashDriveMode* FlashDriveMode = Cast<AFlashDriveMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		FlashDriveMode->bCanCallNextFounder = true;
	}
}