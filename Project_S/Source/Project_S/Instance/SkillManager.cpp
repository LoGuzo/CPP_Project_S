// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManager.h"

SkillManager::SkillManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_SkillTable.DT_SkillTable'"));

	MyData = DATA.Object;
}

SkillManager::~SkillManager()
{
	if (MyCharacter != nullptr)
	{
		MyCharacter.Reset();
	}
}

const TSharedPtr<FTableRowBase> SkillManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FSkillTable>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FSkillTable>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> SkillManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;
	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FSkillTable>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyCharacter = MakeShared<FSkillTable>(*data);
			DataMap.Emplace(data->ID, MyCharacter);
		}
		else
			MyCharacter.Reset();
	}
	return DataMap;
}