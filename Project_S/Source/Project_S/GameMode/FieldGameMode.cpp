// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Project_S/Actor/MonsterSpawner.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Controllers/UserPlayerController.h"
#include "Project_S/Instance/S_GameInstance.h"

AFieldGameMode::AFieldGameMode()
{
	DefaultPawnClass = AUserCharacter::StaticClass();

	PlayerControllerClass = AUserPlayerController::StaticClass();
}

void AFieldGameMode::MonsterFactory()
{
	if (HasAuthority()) // 서버에서만 실행되도록 확인
	{
		auto Data = static_cast<FSpawnData*>(SpawnerData.FindRef(111).Get());
		if (Data)
		{
			AMonsterSpawner* ASpawner = GetWorld()->SpawnActor<AMonsterSpawner>(Data->SpawnerLocation, FRotator(0.f, 30.f, 0.f));
			ASpawner->SetActorScale3D(Data->SpawnerScale);
			ASpawner->SetSpwenerName("Mutant_Spawner");
			ASpawner->SpawnEnemy(Data->SpawnMonster);
		}
	}
}
