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
	auto myCharacter = MyData->FindRow<FMyCharacterData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FMyCharacterData>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}

void MyCharDataManager::SetMyData(FString _RowName, FTableRowBase* _NewData)
{
	MyData->AddRow(FName(*_RowName), *_NewData);
}

void MyCharDataManager::DelMyData(FString _RowName)
{
	MyData->RemoveRow(FName(*_RowName));
}
