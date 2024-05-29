// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API CharacterClassManager : public SGameManagerBase
{
public:
	CharacterClassManager();
	~CharacterClassManager();

	TSharedPtr<FCharacterClass> MyCharacter;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;
};
