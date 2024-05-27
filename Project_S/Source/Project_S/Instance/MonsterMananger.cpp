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
	{
		MyMonster.Reset();
	}
}

const TSharedPtr<FTableRowBase> MonsterMananger::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FMonsterData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
	{
		MyMonster = MakeShared<FMonsterData>(*myCharacter);
	}
	return MyMonster.IsValid() ? MyMonster : nullptr;
}

void MonsterMananger::InsertMonsterManage(int32 Key, FMonsterData Data)
{
	if (MonsterMap.Contains(Key))
		return;

	MonsterMap.Emplace(Key, Data);
}

FMonsterData MonsterMananger::GetMonsterData(int32 Key)
{
	return MonsterMap.FindRef(Key);
}
