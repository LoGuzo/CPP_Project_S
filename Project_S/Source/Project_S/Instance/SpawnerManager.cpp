// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"

SpawnerManager::SpawnerManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>ITEM(TEXT("DataTable'/Game/Data/DT_SpawnerDataTable.DT_SpawnerDataTable'"));

	MyData = ITEM.Object;
}

SpawnerManager::~SpawnerManager()
{
	if (MySpawner.IsValid())
		MySpawner.Reset();
}

const TSharedPtr<FTableRowBase> SpawnerManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FSpawnData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MySpawner = MakeShared<FSpawnData>(*myCharacter);
	else
		MySpawner.Reset();

	return MySpawner.IsValid() ? MySpawner : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> SpawnerManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;

	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FSpawnData>(row[i], row[i].ToString(), false);
		if (data)
		{
			MySpawner = MakeShared<FSpawnData>(*data);
			DataMap.Emplace(data->ID, MySpawner);
		}
		else
			MySpawner.Reset();
	}

	return DataMap;
}