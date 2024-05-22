// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/EnemyCharacter.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CntUser = 0;
	CntMonster = 0;
	CntMiddleBoss = 0;
	CntMiddleBoss = 0;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISION"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMonsterSpawner::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMonsterSpawner::EndOverlap);
}

void AMonsterSpawner::SetCntMonster(int32 _CntMonster)
{
	CntMonster = _CntMonster;
}

void AMonsterSpawner::SetCntMiddleBoss(int32 _CntMiddleBoss)
{
	CntMiddleBoss = _CntMiddleBoss;
}

void AMonsterSpawner::SetCntBoss(int32 _CntBoss)
{
	CntBoss = _CntBoss;
}

void AMonsterSpawner::SetMonsterID(FName _MonsterID)
{
	MonsterID = _MonsterID;
}

void AMonsterSpawner::SetMiddleBossID(FName _MiddleBossID)
{
	MiddleBossID = _MiddleBossID;
}

void AMonsterSpawner::SetBossID(FName _BossID)
{
	BossID = _BossID;
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterSpawner::BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass()->GetSuperClass() == AUserCharacter::StaticClass())
		{
			CntUser++;
		}
	}
}

void AMonsterSpawner::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass()->GetSuperClass() == AUserCharacter::StaticClass())
		{
			CntUser--;
		}
	}
}

void AMonsterSpawner::SetEnemy()
{
	/*for (int32 i = 0; i < CntMonster; i++)
	{
		AEnemyCharacter* NewEnemy = NewObject<AEnemyCharacter>(this, AEnemyCharacter::StaticClass());
		NewEnemy->SetCharID(MonsterID.ToString());
		EnemyArray.Emplace(NewEnemy);
	}

	for (int32 i = 0; i < EnemyArray.Num(); i++)
	{
		//GetWorld()->SpawnActor<AEnemyCharacter>(EnemyArray[i], );
	}*/
}
