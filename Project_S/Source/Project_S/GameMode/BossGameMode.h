// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_SGameMode.h"
#include "BossGameMode.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT_S_API ABossGameMode : public AProject_SGameMode
{
	GENERATED_BODY()

public:
	ABossGameMode();

	virtual void MonsterFactory() override;

protected:
	virtual void BeginPlay() override;

private:
	void SetDelegate();

	UFUNCTION()
		void BossDied();

	TSubclassOf<class AActor> PotalBP;

	TArray<class AEnemyCharacter*> EnemyClassArray;

	void ActivateSlowMotion(float SlowMotionTime, float Duration); // 슬로우 모션함수

	FTimerHandle ResetTimer;

	void ResetSlowMotion(); // 되돌리기
};
