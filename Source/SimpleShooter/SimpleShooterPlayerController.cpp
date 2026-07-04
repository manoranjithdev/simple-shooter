// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterPlayerController.h"

void ASimpleShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
    if (HUDWidgetClass)
    {
        HUDWidget -> AddToViewport();
    }
}



