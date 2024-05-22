// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class PROJECT_S_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	void SetCntMonster(int32 _CntMonster);
	void SetCntMiddleBoss(int32 _CntMiddleBoss);
	void SetCntBoss(int32 _CntBoss);

	void SetMonsterID(FName _MonsterID);
	void SetMiddleBossID(FName _MiddleBossID);
	void SetBossID(FName _BossID);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetEnemy();

	void SpawnEnemy();

private:
	int32 CntUser;
	int32 CntMonster;
	FName MonsterID;
	int32 CntMiddleBoss;
	FName MiddleBossID;
	int32 CntBoss;
	FName BossID;

	TArray<class AEnemyCharacter> EnemyArray;
};
