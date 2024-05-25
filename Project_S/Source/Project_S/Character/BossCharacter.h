// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ABossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	ABossCharacter();

	void SetBossMesh();

	virtual void AnyMove() override;

	virtual void Make_Projectile() override;

	virtual void Set_Projectile() override;
private:
	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* HeadWheel;

	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* Drill;
};
