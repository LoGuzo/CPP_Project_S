// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "SGameManagerBase.h"
/**
 * 
 */
class PROJECT_S_API MyCharDataManager : public SGameManagerBase
{
public:
	MyCharDataManager();
	~MyCharDataManager();

	TSharedPtr<FMyCharacterData> MyCharacter;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;

	virtual void SetMyData(FString _RowName, FTableRowBase* _NewData) override;
};
