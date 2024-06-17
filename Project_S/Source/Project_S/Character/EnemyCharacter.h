// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "Project_S/SUtils.h"
#include "Project_S/S_StructureAll.h"
#include "EnemyCharacter.generated.h"
using namespace SUtils;
DECLARE_MULTICAST_DELEGATE(FOnDied);
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

	virtual void UseSkill(const FString& _SkillName) override;

	void DiedEnemy();

	virtual void AnyMove() {};

	virtual void Make_Projectile() {};

	virtual void Set_Projectile() {};

	virtual void ResetStat() override;

	virtual void LoadCharacterData();

	void SetTarget(class AUserCharacter* _Target);

	void SetEtc();

	E_MonsterType Type;

	void SetState(bool NowState);

	FOnDied OnDied;
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	class AEnemyAIController* NowAIController;

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	class AUserCharacter* Target;
private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	class UOnlyHpBar* OnlyHpBar;

	class UMonsterAnimInstance* AnimInstance;

	class UMaterialInstanceDynamic* MyMaterialInstanceDynamic;

	UC_SkillComponent* Pattern;

	TWeakPtr<FMonsterPattern> NowPattern;

	UPROPERTY()
	FTimerHandle UnusedHandle;

	void SetMesh(TSoftObjectPtr<UStreamableRenderAsset> _MonsterMesh, TSoftObjectPtr<UMaterialInterface> _MonsterMaterial);

	TWeakPtr<FMonsterData> LoadData;

	bool IsReadySpawn;

	TArray<FString> Item;

	void DropItem();
};
