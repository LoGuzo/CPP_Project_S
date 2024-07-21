// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_SGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Actor/MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/BossCharacter.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Instance/S_GameInstance.h"
#include "Project_S/Instance/QuestManager.h"

void AProject_SGameMode::SetQuestCnt()
{
	for (int32 i = 0; i < EnemyClassArray.Num(); i++)
		EnemyClassArray[i]->OnUpdateQuest.AddUObject(this, &AProject_SGameMode::UpdateQuest);
}

AProject_SGameMode::AProject_SGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AUserCharacter::StaticClass();

	PlayerControllerClass = AUserPlayerController::StaticClass();

	UserID.Add("LogH");
	UserID.Add("LogMage");
	UserID.Add("LogHealer");

	UserIndex = 0;
}

void AProject_SGameMode::UpdateQuest(int32 MonsterID)
{
	auto MyInstance = Cast<US_GameInstance>(GetGameInstance());
	if (MyInstance)
	{
		QuestManager->UpdateQuestProgress(MonsterID);
		for (AUserCharacter* UserCharacter : UserCharacters)
		{
			UserCharacter->UpdateQuest(QuestManager->GetNowQuest());
		}
	}
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
		QuestManager = MyInstance->QuestManager;
	}
}

void AProject_SGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		AUserCharacter* UserCharacter = Cast<AUserCharacter>(NewPlayer->GetPawn());
		if (UserCharacter)
		{
			UserCharacter->SetCharID(UserID[UserIndex]);
			UserCharacter->LoadCharacterData();
			UserCharacter->UpdateQuest(QuestManager->GetNowQuest());
			UserCharacters.Add(UserCharacter);
		}
		UserIndex = (UserIndex + 1) % UserID.Num();
	}
}

void AProject_SGameMode::BeginPlay()
{
	Super::BeginPlay();

	MonsterFactory();

	SetQuestCnt();
}

void AProject_SGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	MonsterData.Empty();
	ItemData.Empty();
	SpawnerData.Empty();

	auto MyInstance = Cast<US_GameInstance>(GetGameInstance());
	if (MyInstance)
		MyInstance->SetQuestManager(QuestManager);
}