// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API MonsterPatternManager : public SGameManagerBase
{
public:
	MonsterPatternManager();
	~MonsterPatternManager();

	TSharedPtr<FMonsterPattern> MyCharacter;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;

	TMap<int32, TSharedPtr<FTableRowBase>> GetDataMap() override;
};
