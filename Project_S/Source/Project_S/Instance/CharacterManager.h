// Fill out your copyright notice in the Description page of Project Settings.
#include "SGameManagerBase.h"
#pragma once
class PROJECT_S_API CharacterManager : public SGameManagerBase
{
public:
	CharacterManager();
	~CharacterManager();
	TSharedPtr<FCharacterData> MyCharacter;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;
};
