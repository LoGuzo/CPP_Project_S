// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMananger.h"

MonsterMananger::MonsterMananger()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_MonsterData.DT_MonsterData'"));

	MyData = DATA.Object;
}

MonsterMananger::~MonsterMananger()
{
	if (MyMonster != nullptr)
	{
		MyMonster.Reset();
	}
}

const TSharedPtr<FTableRowBase> MonsterMananger::GetMyData(FString _Init)
{
	auto myCharacter = MyData->FindRow<FMonsterData>(FName(*_Init), TEXT(""), false);
	if (myCharacter)
		MyMonster = MakeShared<FMonsterData>(*myCharacter);
	else
		MyMonster.Reset();
	return MyMonster.IsValid() ? MyMonster : nullptr;
}

TMap<int32, TSharedPtr<FTableRowBase>> MonsterMananger::GetDataMap()
{
	const TArray<FName> row = MyData->GetRowNames();
	TMap<int32, TSharedPtr<FTableRowBase>> DataMap;
	for (int i = 0; i < row.Num(); ++i)
	{
		const auto data = MyData->FindRow<FMonsterData>(row[i], row[i].ToString(), false);
		if (data)
		{
			MyMonster = MakeShared<FMonsterData>(*data);
			DataMap.Emplace(data->ID, MyMonster);
		}
		else
			MyMonster.Reset();
	}
	return DataMap;
}

/*void MonsterMananger::MonsterFactory(FSpawnMonsterData* MonsterData)
{

	switch (MonsterData.MonsterType)
	{
	case E_MonsterType::E_Normal:
	{

	}
	break;
	case E_MonsterType::E_Aggressive:
	{
		AEnemyCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(AEnemyCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
		SpawnNewEnemy->SetCharID(MonsterData->MonsterName.ToString());
		SpawnEnemyAI(SpawnNewEnemy, MonsterData->MonsterType);
		SpawnNewEnemy->SetActorScale3D(MonsterData->MonsterScale);
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
		SpawnNewEnemy->SetCharID(MonsterData->MonsterName.ToString());
		SpawnEnemyAI(SpawnNewEnemy, MonsterData->MonsterType);
		SpawnNewEnemy->SetActorScale3D(MonsterData->MonsterScale);
		SpawnNewEnemy->LoadCharacterData();
		EnemyClassArray.Add(SpawnNewEnemy);
	}
	break;
	case E_MonsterType::E_LastBoss:
	{
		ABossCharacter* SpawnNewEnemy = GetWorld()->SpawnActor<ABossCharacter>(ABossCharacter::StaticClass(), EnemyArray[i].SpawnLocation, FRotator::ZeroRotator);
		SpawnNewEnemy->SetCharID(MonsterData->MonsterName.ToString());
		SpawnEnemyAI(SpawnNewEnemy, MonsterData->MonsterType);
		SpawnNewEnemy->SetActorScale3D(MonsterData->MonsterScale);
		SpawnNewEnemy->LoadCharacterData();
		EnemyClassArray.Add(SpawnNewEnemy);
	}
	break;
	default:
		break;
	}

}

void MonsterMananger::AIFactory(AEnemyCharacter* Enemy, E_MonsterType _MonsterType)
{
	auto* NowAI = Cast<AAIController>(Enemy->GetController());
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
		auto* NewAI = GetWorld()->SpawnActor<AAggressiveAIController>();
		NewAI->Possess(Enemy);
		Enemy->SetEtc();
		Enemy->SetState(false);
	}
	break;
	case E_MonsterType::E_Patrol:
	{

	}
	break;
	case E_MonsterType::E_MiddleBoss:
	{
		auto* NewAI = GetWorld()->SpawnActor<AMiddleBossAIController>();
		NewAI->Possess(Enemy);
		Enemy->SetEtc();
		Enemy->SetState(false);
	}
	break;
	case E_MonsterType::E_LastBoss:
	{
		auto* NewAI = GetWorld()->SpawnActor<AGolemAIController>();
		NewAI->Possess(Enemy);
		Enemy->SetEtc();
		Enemy->SetState(false);
	}
	break;
	default:
		break;
	}
}*/
