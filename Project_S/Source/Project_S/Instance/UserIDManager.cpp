// Fill out your copyright notice in the Description page of Project Settings.


#include "UserIDManager.h"

UserIDManager::UserIDManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_UserID.DT_UserID'"));

	MyData = DATA.Object;
}

UserIDManager::~UserIDManager()
{
	if (MyCharacter != nullptr)
	{
		MyCharacter.Reset();
	}
}

const TSharedPtr<FTableRowBase> UserIDManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FUserID>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FUserID>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}

void UserIDManager::SetMyData(FString _RowName, FTableRowBase* _NewData)
{
	MyData->AddRow(FName(*_RowName), *_NewData);
}