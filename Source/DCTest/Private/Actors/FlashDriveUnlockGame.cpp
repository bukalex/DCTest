// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FlashDriveUnlockGame.h"

AFlashDriveUnlockGame::AFlashDriveUnlockGame()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlashDriveUnlockGame::BeginPlay()
{
	Super::BeginPlay();

	if (ScaledComponentReference.ComponentProperty.IsNone() || !ScaledComponentReference.GetComponent(this))
	{
		ScaledComponent = GetRootComponent();
	}
	else if (USceneComponent* Component = Cast<USceneComponent>(ScaledComponentReference.GetComponent(this)))
	{
		ScaledComponent = Component;
	}
	else
	{
		ScaledComponent = GetRootComponent();
	}

	InitialScale = ScaledComponent->GetComponentScale();
}

void AFlashDriveUnlockGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsLocked) return;

	if (bIsGrowing)
	{
		ScaledComponent->SetWorldScale3D(FMath::VInterpTo(ScaledComponent->GetComponentScale(), TargetScale, DeltaTime, ScalingSpeed));

		if ((ScaledComponent->GetComponentScale() - TargetScale).IsNearlyZero(0.01f))
		{
			bIsGrowing = false;
		}
	}
	else
	{
		ScaledComponent->SetWorldScale3D(FMath::VInterpTo(ScaledComponent->GetComponentScale(), InitialScale, DeltaTime, ScalingSpeed));

		if ((ScaledComponent->GetComponentScale() - InitialScale).IsNearlyZero(0.01f))
		{
			OnDriveUnlocked.Broadcast();
			Destroy();
		}
	}
}

void AFlashDriveUnlockGame::UnlockDrive()
{
	bIsLocked = false;
}