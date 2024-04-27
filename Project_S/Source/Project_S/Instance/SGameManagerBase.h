// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_S/S_StructureAll.h"
/**
 * 
 */
class PROJECT_S_API SGameManagerBase
{
protected:
	class UDataTable* MyData;

public:
	SGameManagerBase() {};

	virtual FTableRowBase* GetMyData(FString _Init) = 0;
	virtual void SetMyData(FString _RowName, FMyCharacterData _NewData) = 0;
};
