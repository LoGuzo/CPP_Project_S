// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "S_StructureAll.h"
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

	FCharacterData* GetStatData(int32 _Level);
	FS_Item* GetItemData(FString _ItemName);

private:

	UPROPERTY();
	class UDataTable* MyStats;

	UPROPERTY();
	class UDataTable* Item;
	
};
