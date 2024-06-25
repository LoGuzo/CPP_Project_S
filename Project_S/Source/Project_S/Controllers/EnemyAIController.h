// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Project_S/EnumClass.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_S_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected :
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	bool IsMoveAtFirst;
	bool IsMoving;
	FVector FirstLocation;

	class AUserCharacter* User;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void LookAtPlayer();

	virtual void AISerach() {}; // ��Ž��
	virtual void AIMove() {}; // �̵�
	virtual void Attack() {}; // ����
	void ResetFirst(); // �ʱ�ȭ
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

	void FSMState(); // ���� ����
	void SetMaxSpeed(float NewMaxSpeed); // MaxSpeed ����

	AUserCharacter* GetUser() { return User; }

	void StartAISearch();
};
