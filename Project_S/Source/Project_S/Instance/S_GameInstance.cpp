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
#include "CharacterClassManager.h"
#include "PartyManager.h"
#include "QuestInfoManager.h"
#include "QuestDataManager.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

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
	MyDataManager.Emplace(E_DataType::E_CharClassData, new CharacterClassManager());
	MyDataManager.Emplace(E_DataType::E_QuestInfo, new QuestInfoManager());
	MyDataManager.Emplace(E_DataType::E_QuestData, new QuestDataManager());
	PartyManager = NewObject<UPartyManager>();
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
		for (auto& data : MyDataManager)
			ZeroMemory(data.Value);
		MyDataManager.Empty();
	}
}

void US_GameInstance::SetUserData(const FUserID& _UserData)
{
	UserData = _UserData;
}

void US_GameInstance::SetUserName(const FString& _UserName)
{
	UserName = _UserName;
}

void US_GameInstance::SetIndex(const int32 _SelectedSlotIndex)
{
	SelectedSlotIndex = _SelectedSlotIndex;
}

void US_GameInstance::NextLevel(const FString& _LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*_LevelName));
}

void US_GameInstance::NextLoadingLevel(const FString& _LevelName)
{
	NextLevelName = _LevelName;
	UGameplayStatics::OpenLevel(GetWorld(), FName("LoadingMap"));
}

void US_GameInstance::Hosting(const FString& MapName)
{
	UserName = TEXT("LogH");
	FString MapPath = FString::Printf(TEXT("%s?listen"), *MapName);
	GetWorld()->ServerTravel(MapPath, true);
}