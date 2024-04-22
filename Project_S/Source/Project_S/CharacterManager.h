// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInBase.h"
#include "S_StructureAll.h"
#include "CharacterManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UCharacterManager : public USInBase
{
	GENERATED_BODY()
public:
	UCharacterManager();

	FCharacterData* GetStatData(int32 _Level);

private:
	UPROPERTY();
	class UDataTable* MyStats;

};
