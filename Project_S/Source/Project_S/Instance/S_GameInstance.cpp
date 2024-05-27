// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameInstance.h"
#include "CharacterManager.h"
#include "ItemManager.h"
#include "MyCharDataManager.h"
#include "SkillManager.h"
#include "MonsterPatternManager.h"
#include "MonsterMananger.h"
#include "SpawnerManager.h"
#include "UserIDManager.h"

US_GameInstance::US_GameInstance()
{
	MyDataManager.Emplace(E_DataType::E_Char, new CharacterManager());
	MyDataManager.Emplace(E_DataType::E_Item, new ItemManager());
	MyDataManager.Emplace(E_DataType::E_MyChar, new MyCharDataManager());
	MyDataManager.Emplace(E_DataType::E_Skill, new SkillManager());
	MyDataManager.Emplace(E_DataType::E_MonsterPattern, new MonsterPatternManager());
	MyDataManager.Emplace(E_DataType::E_MonsterData, new MonsterMananger());
	MyDataManager.Emplace(E_DataType::E_SpawnerData, new SpawnerManager());
	MyDataManager.Emplace(E_DataType::E_UserIDData, new UserIDManager());
}

void US_GameInstance::Init()
{
	Super::Init();
}

void US_GameInstance::Shutdown()
{
	Super::Shutdown();

	if (MyDataManager.Num() != 0)
	{
		MyDataManager.Empty();
	}
}
