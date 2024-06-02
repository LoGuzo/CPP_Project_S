// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/EnemyCharacter.h"
#include "Project_S/Character/MiddleBossCharacter.h"
#include "Project_S/Character/BossCharacter.h"
#include "Project_S/Controllers/AggressiveAIController.h"
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
	if (HasAuthority()) // 서버에서만 실행되도록 확인
	{
		SetEnemy(SpawnerName);
		if (SpawnerName == "Boss_Spawner")
		{
			SpawnEnemy();
		}
	}
}

void AMonsterSpawner::BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass() == AUserCharacter::StaticClass())
		{
			CntUser++;
			if (HasAuthority()) // 서버에서만 실행되도록 확인
			{
				if (CntUser == 1)
				{
					if (!IsSpawn)
					{
						SpawnEnemy();
					}
					else
					{
 						for (int i = 0; i < EnemyClassArray.Num(); i++)
						{
							EnemyClassArray[i]->ResetStat();
						}
					}
				}
			}
		}
	}
}

void AMonsterSpawner::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
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
								EnemyClassArray[i]->DiedEnemy();
							}
						}
					}
				}
			}
		}
	}
}

void AMonsterSpawner::SetEnemy(FString _SpawnerName)
{
	const auto MyGameInstance = Cast<US_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		if (SpawnerName != "") {
			SpawnerData = StaticCastSharedPtr<FSpawnData>(MyGameInstance->MyDataManager.FindRef(E_DataType::E_SpawnerData)->GetMyData(SpawnerName));
			if (SpawnerData.IsValid())
			{
				EnemyArray = SpawnerData.Pin()->SpawnMonster;
			}
		}
	}
}

void AMonsterSpawner::SpawnEnemy()
{
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
			SpawnNewEnemy->SetCharID(EnemyArray[i].ID.ToString());
			SpawnEnemyAI(SpawnNewEnemy, EnemyArray[i].MonsterType);
			SpawnNewEnemy->SetActorScale3D(EnemyArray[i].MonsterScale);
			SpawnNewEnemy->LoadCharacterData();
			EnemyClassArray.Add(SpawnNewEnemy);
		}
		break;
		case E_MonsterType::E_Patrol:
		{

		}
		break;
		case E_MonsterType::E_MiddleBoss:
		{
			AMiddleBossCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<AMiddleBossCharacter>(AMiddleBossCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
			SpawnNewEnemy->SetCharID(EnemyArray[i].ID.ToString());
			SpawnEnemyAI(SpawnNewEnemy, EnemyArray[i].MonsterType);
			SpawnNewEnemy->SetActorScale3D(EnemyArray[i].MonsterScale);
			SpawnNewEnemy->LoadCharacterData();
			EnemyClassArray.Add(SpawnNewEnemy);
		}
		break;
		case E_MonsterType::E_LastBoss:
		{
			ABossCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<ABossCharacter>(ABossCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
			SpawnNewEnemy->SetCharID(EnemyArray[i].ID.ToString());
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
}

void AMonsterSpawner::SpawnEnemyAI(AEnemyCharacter* Enemy, E_MonsterType _MonsterType)
{
	AAIController* NowAI = Cast<AAIController>(Enemy->GetController());
	if (NowAI)
	{
		NowAI->Destroy(); // 기존 AI 컨트롤러 삭제
	}
	switch (_MonsterType)
	{
	case E_MonsterType::E_Normal:
	{

	}
	break;
	case E_MonsterType::E_Aggressive:
	{
		AAggressiveAIController* NewAI = GetWorld()->SpawnActor<AAggressiveAIController>(AAggressiveAIController::StaticClass());
		NewAI->Possess(Enemy);
		Enemy->SetEtc();
	}
	break;
	case E_MonsterType::E_Patrol:
	{

	}
	break;
	case E_MonsterType::E_MiddleBoss:
	{
		AMiddleBossAIController* NewAI = GetWorld()->SpawnActor<AMiddleBossAIController>(AMiddleBossAIController::StaticClass());
		NewAI->Possess(Enemy);
		Enemy->SetEtc();
	}
	break;
	case E_MonsterType::E_LastBoss:
	{
		AGolemAIController* NewAI = GetWorld()->SpawnActor<AGolemAIController>(AGolemAIController::StaticClass());
		NewAI->Possess(Enemy);
		Enemy->SetEtc();
	}
	break;
	default:
		break;
	}
}
