// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API ItemManager : public SGameManagerBase
{
public:
	ItemManager();

	~ItemManager();

	TSharedPtr<FS_Item> MyCharacter;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;
};
