// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum class E_ItemType : uint8
{
	E_Equip UMETA(DisplayName = "Equip"),
	E_Cunsumalbe UMETA(DisplayName = "Cunsum"),
	E_Etc UMETA(DisplayName = "Etc"),
};

UENUM()
enum class E_SkillType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Melee UMETA(DisplayName = "Melee"),
	E_Scope UMETA(DisplayName = "Scope"),
	E_Shot UMETA(DisplayName = "Shot"),
};

UENUM()
enum class E_MonsterType : uint8
{
	E_Normal UMETA(DisplayName = "Normal"),
	E_Aggressive UMETA(DisplayName = "Aggressive"),
	E_Patrol UMETA(DisplayName = "Patrol"),
	E_MiddleBoss UMETA(DisplayName = "MiddleBoss"),
	E_LastBoss UMETA(DisplayName = "LastBoss"),
};

enum class E_DataType : uint8
{
	E_Char,
	E_Item,
	E_MyChar,
	E_Skill,
	E_MonsterPattern,
	E_MonsterData,
	E_SpawnerData,
	E_UserIDData,
	E_CharClassData,
	E_QuestInfo,
	E_QuestData,
};

enum class E_Widget : uint8
{
	E_Main,
	E_HUD,
	E_Set,
	E_PopUp,
};

UENUM()
enum class E_CharClass : uint8
{
	E_Warrior,
	E_Magician,
	E_Healer
};


UENUM()
enum class E_Spanwer : uint8
{
	E_Normal,
	E_Boss,
};

UENUM()
enum class E_QuestInfo : uint8
{
	E_Main,
	E_Sub,
	E_Event,
};
