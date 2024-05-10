// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
class FLocationAndRotator
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
};

enum class E_State
{
	E_Search,
	E_Move,
	E_Attack,
	E_Reset,
};

UCLASS()
class PROJECT_S_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected :
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void PreInitializeComponents() override;
public:
	virtual void Tick(float DeltaTime) override;

	TArray<TSharedPtr<FLocationAndRotator>> PathNode;

	int32 PathIndex;

	float StartTime;
	float EndTime;
	float PlayTime;

	virtual void AISerach() {}; // 적탐색
	virtual void AIMove() {}; // 이동
	void Attack(); // 공격
	void ResetFirst(); // 초기화

	void FSMState();

	E_State ChkState;

	TArray<TSharedPtr<FVector>> Location;
	TArray<TWeakPtr<FVector>> WeakLocation;
};
