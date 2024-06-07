// Fill out your copyright notice in the Description page of Project Settings.


#include "BossGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Project_S/Actor/MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Instance/S_GameInstance.h"


ABossGameMode::ABossGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AUserCharacter::StaticClass();

	PlayerControllerClass = AUserPlayerController::StaticClass();
}

void ABossGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
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

void ABossGameMode::BeginPlay()
{
	Super::BeginPlay();

	MonsterFactory();
}

void ABossGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	MonsterData.Empty();
	ItemData.Empty();
	SpawnerData.Empty();
}

void ABossGameMode::MonsterFactory()
{
	if (HasAuthority()) // 서버에서만 실행되도록 확인
	{
		auto Data = static_cast<FSpawnData*>(SpawnerData.FindRef(112).Get());

		if (Data)
		{
			AMonsterSpawner* ASpawner = GetWorld()->SpawnActor<AMonsterSpawner>(Data->SpawnerLocation, FRotator(0.f, 30.f, 0.f));
			ASpawner->SetActorScale3D(Data->SpawnerScale);
			ASpawner->SpawnEnemy(Data->SpawnMonster);
		}
	}
}