// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_S/S_StructureAll.h"
#include "Project_SGameMode.generated.h"

struct FTableRowBase;

UCLASS(minimalapi)
class AProject_SGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	TArray<FString> UserID;

	int32 UserIndex;

	class UQuestManager* QuestManager;

	TArray<class AUserCharacter*> UserCharacters;

	void UpdateQuest(int32 MonsterID);

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	TArray<class AEnemyCharacter*> EnemyClassArray;

	void SetQuestCnt();

public:
	AProject_SGameMode();

	virtual void MonsterFactory() {};

	TMap<int32, TSharedPtr<FTableRowBase>> MonsterData;
	TMap<int32, TSharedPtr<FTableRowBase>> ItemData;
	TMap<int32, TSharedPtr<FTableRowBase>> SpawnerData;

};



