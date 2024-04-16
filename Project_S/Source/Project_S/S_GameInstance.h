// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "S_GameInstance.generated.h"

USTRUCT()
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExp;

};
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

private:

	UPROPERTY();
	class UDataTable* MyStats;
	
};
