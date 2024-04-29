// Fill out your copyright notice in the Description page of Project Settings.
#include "SGameManagerBase.h"
#pragma once
class PROJECT_S_API CharacterManager : public SGameManagerBase
{
public:
	CharacterManager();

	virtual FCharacterData* GetMyData(FString _Init) override;

	virtual void SetMyData(FString _RowName, FMyCharacterData _NewData) override;
};
