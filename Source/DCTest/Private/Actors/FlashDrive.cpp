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
	BodySprite->OnComponentHit.AddDynamic(this, &AFlashDrive::OnHitSurface);
	BodySprite->SetSprite(bIsLocked ? LockedSprite : UnlockedSprite);
}

void AFlashDrive::StartFalling()
{
	BodySprite->SetEnableGravity(true);
	BodySprite->SetLinearDamping(0.01f);
	BodySprite->SetAngularDamping(0);
	BodySprite->SetCollisionResponseToAllChannels(ECR_Ignore);
	BodySprite->SetCollisionResponseToChannel(ECC_Ground, ECR_Block);
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

void AFlashDrive::OnHitSurface(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (BodySprite->IsGravityEnabled())
	{
		BodySprite->SetEnableGravity(false);
		BodySprite->SetLinearDamping(10);
		BodySprite->SetAngularDamping(10);
		BodySprite->SetCollisionResponseToAllChannels(ECR_Block);
		BodySprite->SetCollisionResponseToChannel(ECC_Ground, ECR_Ignore);
	}
}