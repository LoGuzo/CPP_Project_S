// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_CharacterDataTable.DT_CharacterDataTable'"));

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
	auto myCharacter = MyData->FindRow<FCharacterData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FCharacterData>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}

