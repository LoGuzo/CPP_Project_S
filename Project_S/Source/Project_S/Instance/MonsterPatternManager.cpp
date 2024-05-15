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
	MyCharacter = MakeShared<FMonsterPattern>(*MyData->FindRow<FMonsterPattern>(FName(*_Init), TEXT(""), false));;
	return MyCharacter;
}
