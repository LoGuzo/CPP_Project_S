// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
class AEnemyCharacter;
struct FMonsterPattern;

UCLASS()
class PROJECT_S_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance();
	~UMonsterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Speed;

	TWeakPtr<FMonsterPattern> NowPattern;

	AEnemyCharacter* Monster;

public:
	float GetSpeed() const { return Speed; }
	void SetSpeed(const float _Speed);

	void PlaySome(TWeakPtr<FMonsterPattern>_Data);
	void ColliderNotify();

	void SetMonster(AEnemyCharacter* _Monster);

	UFUNCTION()
	void AnimNotify_Collider();

	UFUNCTION()
	void AnimNotify_AttackEnd();
};
