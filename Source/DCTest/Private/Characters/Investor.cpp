// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Investor.h"

#include "Camera/CameraComponent.h"

AInvestor::AInvestor()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector::ForwardVector * -800);
	Camera->AspectRatio = 1.49f;
}