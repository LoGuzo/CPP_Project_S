// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_SGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Project_S/Actor/MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Instance/S_GameInstance.h"

AProject_SGameMode::AProject_SGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AUserCharacter::StaticClass();

	PlayerControllerClass = AUserPlayerController::StaticClass();
}

void AProject_SGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	auto MyInstance = Cast<US_GameInstance>(GetGameInstance());
	if (MyInstance)
	{
		SpawnerData = MyInstance->MyDataManager.FindRef(E_DataType::E_SpawnerData)->GetDataMap();
		MonsterData = MyInstance->MyDataManager.FindRef(E_DataType::E_MonsterData)->GetDataMap();
		ItemData = MyInstance->MyDataManager.FindRef(E_DataType::E_Item)->GetDataMap();
	}
}

void AProject_SGameMode::BeginPlay()
{
	Super::BeginPlay();

	MonsterFactory();
}

void AProject_SGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	MonsterData.Empty();
	ItemData.Empty();
	SpawnerData.Empty();
}