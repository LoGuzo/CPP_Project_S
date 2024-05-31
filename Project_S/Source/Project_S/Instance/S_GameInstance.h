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

private:
	FString UserName;
	FUserID UserData;
	int32 SelectedSlotIndex = -1;


public:
	US_GameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	TMap<E_DataType, SGameManagerBase*> MyDataManager;

	void SetUserData(const FUserID& _UserData);

	FUserID* GetUserData() { return &UserData; }

	void SetUserName(const FString& _UserName);

	FString GetUserName() { return UserName; }

	void SetIndex(const int32 _SelectedSlotIndex);

	int32 GetIndex() { return SelectedSlotIndex; }

	void NextLevel(const FString& _LevelName);
};
