// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameManagerBase.h"
/**
 * 
 */
class PROJECT_S_API MyCharDataManager : public SGameManagerBase
{
public:
	MyCharDataManager();

	virtual FMyCharacterData* GetMyData(FString _Init) override;

	virtual void SetMyData(FString _RowName, FMyCharacterData _NewData) override;
};
