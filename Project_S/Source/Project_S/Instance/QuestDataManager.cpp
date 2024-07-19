// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestDataManager.h"

QuestDataManager::QuestDataManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_QuestDataTable.DT_QuestDataTable'"));

	MyData = DATA.Object;
}

QuestDataManager::~QuestDataManager()
{
	if (MyQuest != nullptr)
	{
		MyQuest.Reset();
	}
}

const TSharedPtr<FTableRowBase> QuestDataManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FQuestData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyQuest = MakeShared<FQuestData>(*myCharacter);
	else
		MyQuest.Reset();
	return MyQuest.IsValid() ? MyQuest : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> QuestDataManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;
	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FQuestData>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyQuest = MakeShared<FQuestData>(*data);
			DataMap.Emplace(data->ID, MyQuest);
		}
		else
			MyQuest.Reset();
	}
	return DataMap;
}
