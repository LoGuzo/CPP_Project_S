// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Project_S/SUtils.h"
#include "PatrolAIController.generated.h"
using namespace SUtils;

/*class FLocationAndRotator
{
private:
	FVector TargetVector;
	FRotator TargetRotator;
public:
	FLocationAndRotator(FVector _TargetVector, FRotator _TargetRotator)
	{
		TargetVector = _TargetVector;
		TargetRotator = _TargetRotator;
	}
};*/
/**
 * 
 */
UCLASS()
class PROJECT_S_API APatrolAIController : public AEnemyAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	/*TArray<TSharedPtr<FLocationAndRotator>> PathNode;
	TArray<TWeakPtr<FLocationAndRotator>> WeakPathNode;*/

	TArray<FVector> Location;

	int32 PathIndex;

	bool IsFindEnemy;

	virtual void AISerach() override; // ��Ž��
	virtual void AIMove() override; // �̵�
	virtual void Attack() override; // ����

	void MoveToNextPatrolPoint();
public:
	void SetLocation(TArray<FVector> _Location);
};
