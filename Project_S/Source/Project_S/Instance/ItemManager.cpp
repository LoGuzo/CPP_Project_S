// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

ItemManager::ItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>ITEM(TEXT("DataTable'/Game/Data/DT_ItemData.DT_ItemData'"));

	MyData = ITEM.Object;
}

const TSharedPtr<FTableRowBase> ItemManager::GetMyData(FString _Init)
{
	TSharedPtr<FS_Item> MyCharacter;
	return MyCharacter;
}

FS_Item* ItemManager::GetData(FString _Init)
{
	return MyData->FindRow<FS_Item>(FName(*_Init), TEXT(""), false);
}

