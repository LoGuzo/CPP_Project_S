// Fill out your copyright notice in the Description page of Project Settings.


#include "BossGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Project_S/Actor/LevelPotal.h"
#include "Project_S/Actor/MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/BossCharacter.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Instance/S_GameInstance.h"


ABossGameMode::ABossGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AUserCharacter::StaticClass();

	PlayerControllerClass = AUserPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<AActor> BP_Potal(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/BP_LevelPotal.BP_LevelPotal_C'"));
	if (BP_Potal.Succeeded())
	{
		PotalBP = BP_Potal.Class;
	}
}
void ABossGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetDelegate();
}

void ABossGameMode::MonsterFactory()
{
	if (HasAuthority()) // 서버에서만 실행되도록 확인
	{
		auto Data = static_cast<FSpawnData*>(SpawnerData.FindRef(112).Get());

		if (Data)
		{
			AMonsterSpawner* ASpawner = GetWorld()->SpawnActor<AMonsterSpawner>(Data->SpawnerLocation, FRotator(0.f, 30.f, 0.f));
			ASpawner->SetActorScale3D(Data->SpawnerScale);
			ASpawner->SetSpwenerName("Boss_Spawner");
			EnemyClassArray = ASpawner->SpawnEnemy(Data->SpawnMonster);
		}
	}
}

void ABossGameMode::SetDelegate()
{
	for (int32 i = 0; i < EnemyClassArray.Num(); i++)
	{
		if (EnemyClassArray[i]->GetClass() == ABossCharacter::StaticClass())
		{
			EnemyClassArray[i]->OnDied.AddUObject(this, &ABossGameMode::BossDied);
		}
	}
}

void ABossGameMode::BossDied()
{
	ActivateSlowMotion(0.3f, 2.0f);
	if (PotalBP)
	{
		auto LevelPotal =  GetWorld()->SpawnActor<ALevelPotal>(PotalBP, FVector(-7442.f, -5852.f, 226.f), FRotator::ZeroRotator);
		LevelPotal->SetLevelName("DemoMap");
	}
}

void ABossGameMode::ActivateSlowMotion(float SlowMotionTime, float Duration)
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(SlowMotionTime);

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &ABossGameMode::ResetSlowMotion, Duration, false);
}

void ABossGameMode::ResetSlowMotion()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(1.0f);
}
