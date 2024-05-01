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
	E_Etc UMETA(DisplayName = "Etc"),
};

UENUM()
enum class E_SkillType : uint8
{
	E_Melee UMETA(DisplayName = "Melee"),
	E_Scope UMETA(DisplayName = "Scope"),
	E_Shot UMETA(DisplayName = "Shot"),
};

enum class E_DataType : uint8
{
	E_Char,
	E_Item,
	E_MyChar,
	E_Skill,
};
