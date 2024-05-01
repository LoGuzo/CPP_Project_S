// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManager.h"

SkillManager::SkillManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_SkillTable.DT_SkillTable'"));

	MyData = DATA.Object;
}

FSkillTable* SkillManager::GetMyData(FString _Init)
{
	return MyData->FindRow<FSkillTable>(FName(*_Init), TEXT(""), false);
}


