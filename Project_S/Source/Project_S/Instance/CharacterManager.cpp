// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/S_CharacterDataTable.S_CharacterDataTable'"));

	MyData = DATA.Object;
}

CharacterManager::~CharacterManager()
{
	if (MyCharacter != nullptr)
	{
		MyCharacter.Reset();
	}
}
const TSharedPtr<FTableRowBase> CharacterManager::GetMyData(FString _Init)
{
	MyCharacter = MakeShared<FCharacterData>(*MyData->FindRow<FCharacterData>(FName(*_Init), TEXT(""), false));;
	return MyCharacter;
}

