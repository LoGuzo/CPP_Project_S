// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API SpawnerManager : public SGameManagerBase
{
public:
	SpawnerManager();
	~SpawnerManager();

	TSharedPtr<FSpawnData> MySpawner;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;

	TMap<int32, TSharedPtr<FTableRowBase>> GetDataMap() override;
};
