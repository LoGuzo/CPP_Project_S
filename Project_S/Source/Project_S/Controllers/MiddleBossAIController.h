// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Project_S/SUtils.h"
#include "MiddleBossAIController.generated.h"
using namespace SUtils;
/**
 * 
 */
UCLASS()
class PROJECT_S_API AMiddleBossAIController : public AEnemyAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	virtual void AISerach() override; // 적탐색
	virtual void AIMove() override; // 이동
	virtual void Attack() override; // 공격
};
