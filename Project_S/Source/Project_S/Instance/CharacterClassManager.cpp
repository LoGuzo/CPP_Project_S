// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterClassManager.h"

CharacterClassManager::CharacterClassManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_CharacterClass.DT_CharacterClass'"));

	MyData = DATA.Object;
}

CharacterClassManager::~CharacterClassManager()
{
	if (MyCharacter.IsValid())
	{
		MyCharacter.Reset();
	}
}
const TSharedPtr<FTableRowBase> CharacterClassManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FCharacterClass>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FCharacterClass>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}