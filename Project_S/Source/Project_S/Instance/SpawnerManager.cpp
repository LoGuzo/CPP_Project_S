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
	MySpawner = MakeShared<FSpawnData>(*MyData->FindRow<FSpawnData>(FName(*_Init), TEXT(""), false));;
	return MySpawner;
}
