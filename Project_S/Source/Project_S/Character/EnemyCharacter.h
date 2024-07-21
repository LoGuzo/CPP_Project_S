// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstCharacter.h"
#include "Project_S/SUtils.h"
#include "Project_S/S_StructureAll.h"
#include "EnemyCharacter.generated.h"
using namespace SUtils;
DECLARE_MULTICAST_DELEGATE(FOnDied);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateQuest, int32);
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
	FOnUpdateQuest OnUpdateQuest;

	virtual void ShowHpBar();

	virtual void RemoveWidget() {};

	void SetMonsterID(int32 _MonsterID);
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	class AEnemyAIController* NowAIController;

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	class AUserCharacter* Target;

	UPROPERTY(ReplicatedUsing = OnRep_MeshPath)
	USkeletalMesh* MeshPath;

	UPROPERTY(ReplicatedUsing = OnRep_MaterialPath)
	UMaterialInstance* MaterialPath;

	UFUNCTION()
	void OnRep_MeshPath();

	UFUNCTION()
	void OnRep_MaterialPath();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Multi_UseSkill(const FString& _SkillName) override;

	virtual void Multi_UseSkill_Implementation(const FString& SkillName) override;

	void SyncHpBar(AController* PlayerController);
private:
	int32 MonsterID;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	class UOnlyHpBar* OnlyHpBar;

	class UMonsterAnimInstance* AnimInstance;

	class UMaterialInstanceDynamic* MyMaterialInstanceDynamic;

	TWeakPtr<FMonsterPattern> NowPattern;

	UPROPERTY()
	FTimerHandle UnusedHandle;

	void SetMesh(const TSoftObjectPtr<UStreamableRenderAsset>& _MonsterMesh, const TSoftObjectPtr<UMaterialInterface>& _MonsterMaterial);

	TWeakPtr<FMonsterData> LoadData;

	bool IsReadySpawn;

	TArray<FString> Item;

	void DropItem();
};
