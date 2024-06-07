// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

ItemManager::ItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>ITEM(TEXT("DataTable'/Game/Data/DT_ItemData.DT_ItemData'"));

	MyData = ITEM.Object;
}

ItemManager::~ItemManager()
{
	if (MyCharacter != nullptr)
	{
		MyCharacter.Reset();
	}
}

const TSharedPtr<FTableRowBase> ItemManager::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FS_Item>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyCharacter = MakeShared<FS_Item>(*myCharacter);
	else
		MyCharacter.Reset();
	return MyCharacter.IsValid() ? MyCharacter : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> ItemManager::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;
	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FS_Item>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyCharacter = MakeShared<FS_Item>(*data);
			DataMap.Emplace(data->ID, MyCharacter);
		}
		else
			MyCharacter.Reset();
	}
	return DataMap;
}

