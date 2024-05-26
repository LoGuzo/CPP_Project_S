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

	// �ð�
	float StartTime;
	float EndTime;
	float PlayTime;

	virtual void AISerach() {}; // ��Ž��
	virtual void AIMove() {}; // �̵�
	virtual void Attack() {}; // ����
	void ResetFirst(); // �ʱ�ȭ

	void FSMState(); // ���� ����
	void SetMaxSpeed(float NewMaxSpeed); // MaxSpeed ����

	AUserCharacter* GetUser() { return User; }
};
