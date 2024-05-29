// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_S/E_ItemType.h"

/**
 * 
 */
class PROJECT_S_API MappingClass
{
public:
	MappingClass();
	~MappingClass();

	FString GetCharacterDescription(E_CharClass CharacterType);
private:
	UPROPERTY()
	TMap<E_CharClass, FString> CharacterTypeMap;
};
