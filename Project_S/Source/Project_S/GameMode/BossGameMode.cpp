// Fill out your copyright notice in the Description page of Project Settings.


#include "BossGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Project_S/Actor/MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Instance/S_GameInstance.h"


ABossGameMode::ABossGameMode()
{
	// set default pawn class to our Blueprinted character
	DefaultPawnClass = AUserCharacter::StaticClass();

	PlayerControllerClass = AUserPlayerController::StaticClass();
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
			ASpawner->SpawnEnemy(Data->SpawnMonster);
		}
	}
}