// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "AggressiveAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AAggressiveAIController : public AEnemyAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void PreInitializeComponents() override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void AISerach() override; // 적탐색
	virtual void AIMove() override; // 이동
};
