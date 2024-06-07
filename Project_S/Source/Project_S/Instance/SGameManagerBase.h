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
	virtual ~SGameManagerBase() {};
	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) = 0;
	//TWeakPtr 참조자 Pin으로 접근

	virtual void SetMyData(FString _RowName, FTableRowBase* _NewData) {};
	virtual void DelMyData(FString _RowName) {};

	virtual TMap<int32, TSharedPtr<FTableRowBase>>  GetDataMap() { return TMap<int32, TSharedPtr<FTableRowBase>>();}
};
