// Fill out your copyright notice in the Description page of Project Settings.


#include "MappingClass.h"

MappingClass::MappingClass()
{
    CharacterTypeMap.Add(E_CharClass::E_Warrior, TEXT("Warrior"));
    CharacterTypeMap.Add(E_CharClass::E_Magician, TEXT("Magician"));
    CharacterTypeMap.Add(E_CharClass::E_Healer, TEXT("Healer"));
}

MappingClass::~MappingClass()
{
	if (CharacterTypeMap.Num() != 0)
	{
		CharacterTypeMap.Empty();
	}
}

FString MappingClass::GetCharacterDescription(E_CharClass CharacterType)
{
	return CharacterTypeMap.Contains(CharacterType) ? CharacterTypeMap[CharacterType] : TEXT("Unknown");
}

