// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

ALobbyController::ALobbyController()
{
	bShowMouseCursor = true;
}

void ALobbyController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	SetIgnoreLookInput(true);
}