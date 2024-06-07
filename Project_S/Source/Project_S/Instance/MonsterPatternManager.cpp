// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPatternManager.h"

MonsterPatternManager::MonsterPatternManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_MonsterPattern.DT_MonsterPattern'"));

	MyData = DATA.Object;
}

MonsterPatternManager::~MonsterPatternManager()
{
	if (MyCharacter != nullptr)
	{
		MyCharacter.Reset();
	}
}
const TSharedPtr<FTableRowBase> MonsterPatternManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FMonsterPattern>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FMonsterPattern>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> MonsterPatternManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;
	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FMonsterPattern>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyCharacter = MakeShared<FMonsterPattern>(*data);
			DataMap.Emplace(data->ID, MyCharacter);
		}
		else
			MyCharacter.Reset();
	}
	return DataMap;
}