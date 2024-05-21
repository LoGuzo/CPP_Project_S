// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMananger.h"

MonsterMananger::MonsterMananger()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_MonsterPattern.DT_MonsterPattern'"));

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
	MyMonster = MakeShared<FMonsterData>(*MyData->FindRow<FMonsterData>(FName(*_Init), TEXT(""), false));;
	return MyMonster;
}

void MonsterMananger::AddMonsterManage(int32 Key)
{
	if (MonsterMap.Contains(Key))
		return;

	FMonsterData data;

	//int32 Key = data.ID;

	MonsterMap.Emplace(Key, data);
}

FMonsterData MonsterMananger::GetMonsterData(int32 Key)
{
	return MonsterMap.FindRef(Key);
}
