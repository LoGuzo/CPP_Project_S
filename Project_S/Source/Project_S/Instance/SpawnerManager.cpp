// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"

SpawnerManager::SpawnerManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>ITEM(TEXT("DataTable'/Game/Data/DT_SpawnerDataTable.DT_SpawnerDataTable'"));

	MyData = ITEM.Object;
}

SpawnerManager::~SpawnerManager()
{
	if (MySpawner != nullptr)
	{
		MySpawner.Reset();
	}
}

const TSharedPtr<FTableRowBase> SpawnerManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FSpawnData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
	{
		MySpawner = MakeShared<FSpawnData>(*myCharacter);
	}
	return MySpawner.IsValid() ? MySpawner : nullptr;
}
