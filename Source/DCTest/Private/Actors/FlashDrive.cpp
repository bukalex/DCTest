// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FlashDrive.h"

#include "Components/DraggableSpriteComponent.h"

AFlashDrive::AFlashDrive()
{
	PrimaryActorTick.bCanEverTick = false;

	BodySprite = CreateDefaultSubobject<UDraggableSpriteComponent>("BodySprite");
	SetRootComponent(BodySprite);
}