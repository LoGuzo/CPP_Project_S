// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Project_S/S_StructureAll.h"
#include "SGameManagerBase.h"
#include "S_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API US_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	US_GameInstance();

	virtual void Init() override;

	/*FCharacterData* GetStatData(int32 _Level);
	FS_Item* GetItemData(FString _ItemName);*/
	TMap<FString, SGameManagerBase*> MyDataManager;
private:
/*
	UPROPERTY();
	class UDataTable* MyStats;

	UPROPERTY();
	class UDataTable* Item;*/
	
};
