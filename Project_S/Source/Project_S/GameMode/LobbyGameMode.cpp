// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Project_S/Controllers/LobbyController.h"

ALobbyGameMode::ALobbyGameMode()
{
	PlayerControllerClass = ALobbyController::StaticClass();
}
