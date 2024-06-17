// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Project_S/S_StructureAll.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class PROJECT_S_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	void SetSpwenerName(FString _SpawnerName);

	TArray<class AEnemyCharacter*> SpawnEnemy(TArray<FSpawnMonsterData> _EnemyArray);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SpawnEnemyAI(class AEnemyCharacter* Enemy, E_MonsterType _MonsterType);

private:
	TWeakPtr<FSpawnData> SpawnerData;

	UPROPERTY(EditAnywhere)
	FString SpawnerName;

	int32 CntUser;

	TArray<FSpawnMonsterData> EnemyArray;

	TArray<class AEnemyCharacter*> EnemyClassArray;

	bool IsSpawn;
};
