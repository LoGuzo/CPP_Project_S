// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeCharGameMode.h"
#include "Project_S/Actor/MakeCharacterPawn.h"
#include "Project_S/Controllers/MakeCharController.h"

AMakeCharGameMode::AMakeCharGameMode()
{
	DefaultPawnClass = AMakeCharacterPawn::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController>PC(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/BP_MakeCharController.BP_MakeCharController_C'"));
	if (PC.Succeeded())
		PlayerControllerClass = PC.Class;
}