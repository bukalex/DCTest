// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Laptop.h"

#include "PaperSpriteComponent.h"
#include "Components/USBPortComponent.h"

ALaptop::ALaptop()
{
	PrimaryActorTick.bCanEverTick = false;

	BodySprite = CreateDefaultSubobject<UPaperSpriteComponent>("BodySprite");
	SetRootComponent(BodySprite);

	USBPort = CreateDefaultSubobject<UUSBPortComponent>("USBSprite");
	USBPort->SetupAttachment(GetRootComponent());
}
