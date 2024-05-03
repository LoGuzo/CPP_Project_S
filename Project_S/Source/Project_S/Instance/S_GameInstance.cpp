// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GameInstance.h"
#include "CharacterManager.h"
#include "ItemManager.h"
#include "MyCharDataManager.h"
#include "SkillManager.h"

US_GameInstance::US_GameInstance()
{

	MyDataManager.Add(E_DataType::E_Char, new CharacterManager());
	MyDataManager.Add(E_DataType::E_Item, new ItemManager());
	MyDataManager.Add(E_DataType::E_MyChar, new MyCharDataManager());
	MyDataManager.Add(E_DataType::E_Skill, new SkillManager());

}

void US_GameInstance::Init()
{
	Super::Init();
}

void US_GameInstance::Shutdown()
{
	Super::Shutdown();
}
