// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Project_S/EnumClass.h"
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

UCLASS()
class PROJECT_S_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected :
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void PreInitializeComponents() override;

	TArray<TSharedPtr<FLocationAndRotator>> PathNode;
	TArray<TWeakPtr<FLocationAndRotator>> WeakPathNode;
	int32 PathIndex;

	bool IsMoveAtFirst;
	bool IsMoving;
	FVector FirstLocation;

	TArray<TSharedPtr<FVector>> Location;
	TArray<TWeakPtr<FVector>> WeakLocation;

	class AUserCharacter* User;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	bool IsDead;
	E_State ChkState;
	bool IsBackToTheHome;
	int32 CountSearch;
	virtual void Tick(float DeltaTime) override;

	// 시간
	float StartTime;
	float EndTime;
	float PlayTime;

	virtual void AISerach() {}; // 적탐색
	virtual void AIMove() {}; // 이동
	virtual void Attack() {}; // 공격
	void ResetFirst(); // 초기화

	void FSMState(); // 상태 변경
	void SetMaxSpeed(float NewMaxSpeed); // MaxSpeed 조정

	AUserCharacter* GetUser() { return User; }
};
