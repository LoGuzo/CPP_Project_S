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
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void PreInitializeComponents() override;

	TArray<TSharedPtr<FLocationAndRotator>> PathNode;
	int32 PathIndex;
	bool IsMoveAtFirst;
	bool IsMoving;
	E_State ChkState;
	FVector FirstLocation;

	TArray<TSharedPtr<FVector>> Location;
	TArray<TWeakPtr<FVector>> WeakLocation;

	class AUserCharacter* User;

public:
	bool IsBackToTheHome;
	int32 CountSearch;
	virtual void Tick(float DeltaTime) override;

	float StartTime;
	float EndTime;
	float PlayTime;

	virtual void AISerach() {}; // 적탐색
	virtual void AIMove() {}; // 이동
	virtual void Attack() {}; // 공격
	void ResetFirst(); // 초기화

	void FSMState();
};
