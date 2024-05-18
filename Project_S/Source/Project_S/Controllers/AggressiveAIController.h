// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Project_S/SUtils.h"
#include "AggressiveAIController.generated.h"
using namespace SUtils;
/**
 * 
 */
UCLASS()
class PROJECT_S_API AAggressiveAIController : public AEnemyAIController
{
	GENERATED_BODY()

protected:

	virtual void PreInitializeComponents() override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void AISerach() override; // ��Ž��
	virtual void AIMove() override; // �̵�
	virtual void Attack() override; // ����
};
