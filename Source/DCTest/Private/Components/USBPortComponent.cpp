// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/USBPortComponent.h"

#include "Actors/FlashDrive.h"

void UUSBPortComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UUSBPortComponent::OnDriveBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UUSBPortComponent::OnDriveEndOverlap);
}

void UUSBPortComponent::OnDriveBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (InsertedDrive) return;

	if (AFlashDrive* Drive = Cast<AFlashDrive>(OtherActor))
	{
		OnFlashDriveDetected.Broadcast(Drive);
		InsertedDrive = Drive;
	}
}

void UUSBPortComponent::OnDriveEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!InsertedDrive) return;

	if (AFlashDrive* Drive = Cast<AFlashDrive>(OtherActor))
	{
		if (Drive != InsertedDrive) return;

		OnFlashDriveLost.Broadcast(Drive);
		InsertedDrive = nullptr;
	}
}