// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameInstance.h"

US_GameInstance::US_GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/S_CharacterDataTable.S_CharacterDataTable'"));

	MyStats = DATA.Object;
}

void US_GameInstance::Init()
{
	Super::Init();
}

FCharacterData* US_GameInstance::GetStatData(int32 _Level)
{
	return MyStats->FindRow<FCharacterData>(*FString::FromInt(_Level),TEXT(""));
}
