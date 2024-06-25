// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/EnemyCharacter.h"
#include "Project_S/Character/MiddleBossCharacter.h"
#include "Project_S/Character/BossCharacter.h"
#include "Project_S/Controllers/AggressiveAIController.h"
#include "Project_S/Controllers/PatrolAIController.h"
#include "Project_S/Controllers/MiddleBossAIController.h"
#include "Project_S/Controllers/GolemAIController.h"
#include "Project_S/Instance/S_GameInstance.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CntUser = 0;
	IsSpawn = false;
	SpawnerName = "Mutant_Spawner";

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISION"));
	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMonsterSpawner::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMonsterSpawner::EndOverlap);
}

void AMonsterSpawner::SetSpwenerName(FString _SpawnerName)
{
	SpawnerName = _SpawnerName;
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterSpawner::BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpawnerName == "Boss_Spawner")
		return;
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass() == AUserCharacter::StaticClass())
		{
			CntUser++;
			if (HasAuthority()) // 서버에서만 실행되도록 확인
			{
				if (CntUser == 1)
				{
 					for (int i = 0; i < EnemyClassArray.Num(); i++)
					{
						EnemyClassArray[i]->SetState(true);
					}
				}
			}
		}
	}
}

void AMonsterSpawner::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (SpawnerName == "Boss_Spawner")
		return;
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass() == AUserCharacter::StaticClass())
		{
			if (CntUser > 0)
			{
				CntUser--;
				if (HasAuthority()) // 서버에서만 실행되도록 확인
				{
					if (CntUser == 0)
					{
						if (IsSpawn)
						{
							for (int32 i = 0; i < EnemyClassArray.Num(); i++)
							{
								EnemyClassArray[i]->SetState(false);
							}
						}
					}
				}
			}
		}
	}
}

TArray<AEnemyCharacter*> AMonsterSpawner::SpawnEnemy(TArray<FSpawnMonsterData> _EnemyArray)
{
	EnemyArray = _EnemyArray;
	for (int32 i = 0; i < EnemyArray.Num(); i++)
	{
		switch (EnemyArray[i].MonsterType)
		{
		case E_MonsterType::E_Normal:
		{

		}
		break;
		case E_MonsterType::E_Aggressive:
		{
			AEnemyCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(AEnemyCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
			SpawnNewEnemy->SetCharID(EnemyArray[i].MonsterName.ToString());
			SpawnEnemyAI(SpawnNewEnemy, EnemyArray[i].MonsterType);
			SpawnNewEnemy->SetActorScale3D(EnemyArray[i].MonsterScale);
			SpawnNewEnemy->LoadCharacterData();
			EnemyClassArray.Add(SpawnNewEnemy);
		}
		break;
		case E_MonsterType::E_Patrol:
		{
			AEnemyCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(AEnemyCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
			SpawnNewEnemy->SetCharID(EnemyArray[i].MonsterName.ToString());
			APatrolAIController* NewAI = Cast<APatrolAIController>(SpawnEnemyAI(SpawnNewEnemy, EnemyArray[i].MonsterType));
			if (NewAI)
			{
				NewAI->SetLocation(EnemyArray[i].PatrolLocation); // 패트롤 정보 설정
			}
			SpawnNewEnemy->SetActorScale3D(EnemyArray[i].MonsterScale);
			SpawnNewEnemy->LoadCharacterData();
			EnemyArray[i].PatrolLocation;
			EnemyClassArray.Add(SpawnNewEnemy);
		}
		break;
		case E_MonsterType::E_MiddleBoss:
		{
			AMiddleBossCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<AMiddleBossCharacter>(AMiddleBossCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
			SpawnNewEnemy->SetCharID(EnemyArray[i].MonsterName.ToString());
			SpawnEnemyAI(SpawnNewEnemy, EnemyArray[i].MonsterType);
			SpawnNewEnemy->SetActorScale3D(EnemyArray[i].MonsterScale);
			SpawnNewEnemy->LoadCharacterData();
			EnemyClassArray.Add(SpawnNewEnemy);
		}
		break;
		case E_MonsterType::E_LastBoss:
		{
			ABossCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<ABossCharacter>(ABossCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
			SpawnNewEnemy->SetCharID(EnemyArray[i].MonsterName.ToString());
			SpawnEnemyAI(SpawnNewEnemy, EnemyArray[i].MonsterType);
			SpawnNewEnemy->SetActorScale3D(EnemyArray[i].MonsterScale);
			SpawnNewEnemy->LoadCharacterData();
			EnemyClassArray.Add(SpawnNewEnemy);
		}
		break;
		default:
		break;
		}
	}
	IsSpawn = true;

	return EnemyClassArray;
}

AAIController* AMonsterSpawner::SpawnEnemyAI(AEnemyCharacter* Enemy, E_MonsterType _MonsterType)
{
	AAIController* NowAI = Cast<AAIController>(Enemy->GetController());
	if (NowAI)
	{
		NowAI->Destroy(); // 기존 AI 컨트롤러 삭제
	}
	AAIController* NewAI = nullptr;
	switch (_MonsterType)
	{
	case E_MonsterType::E_Normal:
	{

	}
	break;
	case E_MonsterType::E_Aggressive:
	{
		NewAI = GetWorld()->SpawnActor<AAggressiveAIController>(AAggressiveAIController::StaticClass());
	}
	break;
	case E_MonsterType::E_Patrol:
	{
		NewAI = GetWorld()->SpawnActor<APatrolAIController>(APatrolAIController::StaticClass());
	}
	break;
	case E_MonsterType::E_MiddleBoss:
	{
		NewAI = GetWorld()->SpawnActor<AMiddleBossAIController>(AMiddleBossAIController::StaticClass());
	}
	break;
	case E_MonsterType::E_LastBoss:
	{
		NewAI = GetWorld()->SpawnActor<AGolemAIController>(AGolemAIController::StaticClass());
	}
	break;
	default:
	break;
	}
	NewAI->Possess(Enemy);
	Enemy->SetEtc();
	Enemy->SetState(false);

	return NewAI;
}
