// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "Project_S/S_StructureAll.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
class UC_SkillComponent;
UCLASS()
class PROJECT_S_API AEnemyCharacter : public AFirstCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	virtual void UseSkill(FString _SkillName) override;

	void DiedEnemy();

	virtual void AnyMove() {};

	virtual void Make_Projectile() {};

	virtual void Set_Projectile() {};

	virtual void ResetStat() override;

	void LoadCharacterData();

	void SetEtc();

	E_MonsterType Type;
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	class UOnlyHpBar* OnlyHpBar;

	class UMonsterAnimInstance* AnimInstance;

	class UMaterialInstanceDynamic* MyMaterialInstanceDynamic;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PostInitializeComponents() override;

	bool IsDead;

	UC_SkillComponent* Pattern;

	TWeakPtr<FMonsterPattern> NowPattern;

	UPROPERTY()
	FTimerHandle UnusedHandle;

	virtual void SetMesh(TSoftObjectPtr<UStreamableRenderAsset> _MonsterMesh, TSoftObjectPtr<UMaterialInterface> _MonsterMaterial) override;

	TWeakPtr<FMonsterData> LoadData;

	class AEnemyAIController* NowAIController;

	bool IsReadySpawn;

};
