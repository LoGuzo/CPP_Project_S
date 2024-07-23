// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInfoManager.h"

QuestInfoManager::QuestInfoManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_QuestInfoDataTable.DT_QuestInfoDataTable'"));

	MyData = DATA.Object;
}

QuestInfoManager::~QuestInfoManager()
{
	if (MyQuestInfo != nullptr)
		MyQuestInfo.Reset();
}

const TSharedPtr<FTableRowBase> QuestInfoManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FQuestInfoData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyQuestInfo = MakeShared<FQuestInfoData>(*myCharacter);
	else
		MyQuestInfo.Reset();

	return MyQuestInfo.IsValid() ? MyQuestInfo : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> QuestInfoManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;

	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FQuestInfoData>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyQuestInfo = MakeShared<FQuestInfoData>(*data);
			DataMap.Emplace(data->ID, MyQuestInfo);
		}
		else
			MyQuestInfo.Reset();
	}

	return DataMap;
}
