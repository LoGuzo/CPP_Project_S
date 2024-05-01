// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameInstance.h"
#include "CharacterManager.h"
#include "ItemManager.h"
#include "MyCharDataManager.h"
#include "SkillManager.h"

US_GameInstance::US_GameInstance()
{
	/*static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/S_CharacterDataTable.S_CharacterDataTable'"));

	MyStats = DATA.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable>ITEM(TEXT("DataTable'/Game/Data/DT_ItemData.DT_ItemData'"));

	Item = ITEM.Object;*/

	MyDataManager.Add(E_DataType::E_Char, new CharacterManager());
	MyDataManager.Add(E_DataType::E_Item, new ItemManager());
	MyDataManager.Add(E_DataType::E_MyChar, new MyCharDataManager());
	MyDataManager.Add(E_DataType::E_Skill, new SkillManager());

}

void US_GameInstance::Init()
{
	Super::Init();
}

/*FCharacterData* US_GameInstance::GetStatData(int32 _Level)
{
	return MyStats->FindRow<FCharacterData>(*FString::FromInt(_Level),TEXT(""), false);
}

FS_Item* US_GameInstance::GetItemData(FString _ItemName)
{
	return Item->FindRow<FS_Item>(FName(*_ItemName),TEXT(""), false);
}*/
