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
	MyCharacter = MakeShared<FSkillTable>(*MyData->FindRow<FSkillTable>(FName(*_Init), TEXT(""), false));;
	return MyCharacter;
}

FSkillTable* SkillManager::GetData(FString _Init)
{
	return MyData->FindRow<FSkillTable>(FName(*_Init), TEXT(""), false);
}


