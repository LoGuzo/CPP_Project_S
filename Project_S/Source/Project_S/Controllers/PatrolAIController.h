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
	virtual void AISerach() override; // ��Ž��
	virtual void AIMove() override; // �̵�
	virtual void Attack() override; // ����

	void MoveToNextPatrolPoint();
public:
	void SetLocation(TArray<FVector> _Location);
};
