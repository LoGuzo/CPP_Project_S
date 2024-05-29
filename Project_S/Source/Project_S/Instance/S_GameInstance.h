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
	FString UserID;
	FString UserName;
public:
	US_GameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	TMap<E_DataType, SGameManagerBase*> MyDataManager;
	
	UFUNCTION(BlueprintCallable)
	void SetUserID(const FString& _UserID);

	UFUNCTION(BlueprintCallable)
	FString GetUserID() { return UserID; }

	UFUNCTION(BlueprintCallable)
	void SetUserName(const FString& _UserName);
};
