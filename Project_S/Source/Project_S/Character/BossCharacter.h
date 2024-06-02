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

	virtual void LoadCharacterData() override;
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PostInitializeComponents() override;
private:
	TSubclassOf<class UW_BossHp> U_BossHp;
	class UW_BossHp* W_BossHp;

	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* HeadWheel;

	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* Drill;
};
