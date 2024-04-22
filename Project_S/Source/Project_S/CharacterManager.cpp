// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"

UCharacterManager::UCharacterManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/S_CharacterDataTable.S_CharacterDataTable'"));

	MyStats = DATA.Object;
}

FCharacterData* UCharacterManager::GetStatData(int32 _Level)
{
	return MyStats->FindRow<FCharacterData>(*FString::FromInt(_Level), TEXT(""), false);
}