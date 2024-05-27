// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "Project_S/Controllers/LoginController.h"

ALoginGameMode::ALoginGameMode()
{
	PlayerControllerClass = ALoginController::StaticClass();
}