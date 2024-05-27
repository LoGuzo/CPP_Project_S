// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API UserIDManager : public SGameManagerBase
{
public:
	UserIDManager();
	~UserIDManager();

	TSharedPtr<FUserID> MyCharacter;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;

	virtual void SetMyData(FString _RowName, FTableRowBase* _NewData) override;
};
