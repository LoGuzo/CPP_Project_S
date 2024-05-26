// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Project_S/SUtils.h"
#include "GolemAIController.generated.h"
using namespace SUtils;
/**
 * 
 */
UCLASS()
class PROJECT_S_API AGolemAIController : public AEnemyAIController
{
	GENERATED_BODY()
private:
	TArray<float> CoolTime;

	UPROPERTY()
	FTimerHandle SearchHandle;
	UPROPERTY()
	TArray<FTimerHandle> SkillCooldownHandles;
	TArray<class AUserCharacter*> SearchChacter;
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void AISerach() override; // 적탐색
	virtual void AIMove() override; // 이동
	virtual void Attack() override; // 공격

	void LookAtPlayer();
	void SetRandomCharacter();

	void OnSkillCooldownComplete(int32 SkillIndex); // 쿨타임
	bool IsSkillOnCooldown(int32 SkillIndex) const; // 쿨타임 확인
};
