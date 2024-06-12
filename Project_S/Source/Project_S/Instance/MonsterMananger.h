// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API MonsterMananger : public SGameManagerBase
{
public:
	MonsterMananger();
	~MonsterMananger();
	TSharedPtr<FMonsterData> MyMonster;

	virtual const TSharedPtr<FTableRowBase> GetMyData(FString _Init) override;

	TMap<int32, TSharedPtr<FTableRowBase>> GetDataMap() override;

	/*void MonsterFactory(FSpawnMonsterData* MonsterData);
	void AIFactory(AEnemyCharacter* Enemy, E_MonsterType _MonsterType);*/
};
