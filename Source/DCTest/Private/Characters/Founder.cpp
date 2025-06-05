// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Founder.h"

#include "PaperFlipbookComponent.h"
#include "Actors/FlashDrive.h"
#include "GameFramework/CharacterMovementComponent.h"

void AFounder::BeginPlay()
{
	Super::BeginPlay();

	GetSprite()->OnClicked.AddDynamic(this, &AFounder::OnClicked);
}

void AFounder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		if ((Destination - GetActorLocation()).IsNearlyZero(10))
		{
			bIsMoving = false;
		}
		else
		{
			SetActorLocation(FMath::VInterpTo(GetActorLocation(), Destination, DeltaTime, GetCharacterMovement()->GetMaxSpeed()));
		}
	}
}

void AFounder::GoToLocation(const FVector& Location)
{
	bIsMoving = true;
	Destination = Location;

	if (FlashDrive) FlashDrive->Destroy();
}

void AFounder::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (bIsMoving) return;
	if (!FlashDriveClass) return;
	if (FlashDrive) return;

	FVector DriveLocation = GetActorLocation();
	DriveLocation.Y = DriveYOrder;

	FlashDrive = GetWorld()->SpawnActor<AFlashDrive>(FlashDriveClass, DriveLocation, FRotator());
	FlashDrive->StartFalling();
}