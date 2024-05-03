// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/S_CharacterDataTable.S_CharacterDataTable'"));

	MyData = DATA.Object;
}
/*const TSharedPtr<FTableRowBase> CharacterManager::GetMyData(FString _Init)
{
	TSharedPtr<FCharacterData> MyCharacter;
	return MyData->FindRow<FCharacterData>(FName(*_Init), TEXT(""), false);
}*/
FCharacterData* CharacterManager::GetMyData(FString _Init)
{
	return MyData->FindRow<FCharacterData>(FName(*_Init), TEXT(""), false);
}

