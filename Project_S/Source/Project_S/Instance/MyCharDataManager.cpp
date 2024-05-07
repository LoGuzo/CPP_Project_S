// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharDataManager.h"

MyCharDataManager::MyCharDataManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_MyCharacterDataTable.DT_MyCharacterDataTable'"));

	MyData = DATA.Object;
}
MyCharDataManager::~MyCharDataManager()
{
	if (MyCharacter != nullptr)
	{
		MyCharacter.Reset();
	}
}

const TSharedPtr<FTableRowBase> MyCharDataManager::GetMyData(FString _Init)
{
	MyCharacter = MakeShared<FMyCharacterData>(*MyData->FindRow<FMyCharacterData>(FName(*_Init), TEXT(""), false));;
	return MyCharacter;
}

void MyCharDataManager::SetMyData(FString _RowName, FMyCharacterData _NewData)
{
	MyData->AddRow(FName(*_RowName), _NewData);
}
