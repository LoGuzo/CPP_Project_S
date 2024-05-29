// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_SGameMode.h"
#include "Project_S/Character/UserCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_SGameMode::AProject_SGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AUserCharacter::StaticClass();
}
