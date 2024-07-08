// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Project_S/SUtils.h"
#include "AStarAIController.generated.h"
using namespace SUtils;
/**
 * 
 */

enum class NowState
{
	E_Walk,
	E_Stop
};

UCLASS()
class PROJECT_S_API AAStarAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	AAStarAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	TArray<FVector> Location;
	TArray<FVector> DetailPath;

	NowState WalkStop;

	int32 PathIndex;

	int32 DetailPathIndex;

	class APathFinder* PathFinder;
protected:
	virtual void AIMove() override; // ¿Ãµø

	void MoveToNextPatrolPoint();

	// UsingAStar PathFinder
	void MoveToLocationUsingAStar(const FVector& TargetLocation);

	void MoveFoward(float DeltaTime);
public:
	void SetLocation(const TArray<FVector>& _Location);
};
