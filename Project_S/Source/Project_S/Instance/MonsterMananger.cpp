// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMananger.h"

MonsterMananger::MonsterMananger()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_MonsterData.DT_MonsterData'"));

	MyData = DATA.Object;
}

MonsterMananger::~MonsterMananger()
{
	if (MyMonster != nullptr)
		MyMonster.Reset();
}

const TSharedPtr<FTableRowBase> MonsterMananger::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FMonsterData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyMonster = MakeShared<FMonsterData>(*myCharacter);
	else
		MyMonster.Reset();

	return MyMonster.IsValid() ? MyMonster : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> MonsterMananger::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;

	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FMonsterData>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyMonster = MakeShared<FMonsterData>(*data);
			DataMap.Emplace(data->ID, MyMonster);
		}
		else
			MyMonster.Reset();
	}

	return DataMap;
}