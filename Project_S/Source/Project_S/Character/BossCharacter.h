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

	virtual void ShowHpBar();

	virtual void RemoveWidget() override;

	void StartAISearch();
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	int32 CntMissile;

	TSubclassOf<class AProjectile_Missle> ProjectileClass;
	
	FVector MuzzleOffset;

	TSubclassOf<class UW_BossHp> U_BossHp;
	class UW_BossHp* W_BossHp;

	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* HeadWheel;

	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* Drill;

	TArray<class AProjectile_Missle*> MyProjectiles;

	FVector SetMissleLocation();

	UPROPERTY()
	FTimerHandle RemoveWidgetHandle;

	bool BossDied;
};
