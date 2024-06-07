// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BossGameMode.generated.h"
struct FTableRowBase;
/**
 * 
 */
UCLASS()
class PROJECT_S_API ABossGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	TMap<int32, TSharedPtr<FTableRowBase>> MonsterData;
	TMap<int32, TSharedPtr<FTableRowBase>> ItemData;
	TMap<int32, TSharedPtr<FTableRowBase>> SpawnerData;
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	ABossGameMode();

	void MonsterFactory();
};
