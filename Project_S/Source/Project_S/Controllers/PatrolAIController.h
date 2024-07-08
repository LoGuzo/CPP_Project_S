// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Project_S/SUtils.h"
#include "PatrolAIController.generated.h"
using namespace SUtils;


UCLASS()
class PROJECT_S_API APatrolAIController : public AEnemyAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TArray<FVector> Location;

	int32 PathIndex;

	bool IsFindEnemy;
	
protected:
	virtual void AISerach() override; // 적탐색
	virtual void AIMove() override; // 이동
	virtual void Attack() override; // 공격

	void MoveToNextPatrolPoint();
public:
	void SetLocation(TArray<FVector> _Location);
};
