// Fill out your copyright notice in the Description page of Project Settings.


#include "BossGameMode.h"
#include "LevelSequencePlayer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
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
		PotalBP = BP_Potal.Class;

	static ConstructorHelpers::FObjectFinder<ULevelSequence> Boss_Seq(TEXT("LevelSequence'/Game/Ancient_Golem/BossSequence.BossSequence'"));
	if (Boss_Seq.Succeeded())
		BossSequence = Boss_Seq.Object;
}
void ABossGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &ABossGameMode::DelayedStart, 5.f, false);
}

void ABossGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EnemyClassArray.Num() != 0)
		EnemyClassArray.Reset();
	if (ConnectedPlayers.Num() != 0)
		ConnectedPlayers.Reset();
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

void ABossGameMode::MulticastPlayLevelSequence_Implementation()
{
	if (!BossSequence) 
		return;

	ALevelSequenceActor* ContextActor = nullptr;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), BossSequence, FMovieSceneSequencePlaybackSettings(), ContextActor);

	if (SequencePlayer)
	{
		SequencePlayer->OnFinished.AddDynamic(this, &ABossGameMode::OnCinematicFinished);
		SequencePlayer->Play();
	}
}

void ABossGameMode::PlayCinematic()
{
	if (HasAuthority()) // Ensure this is running on the server
	{
		MulticastPlayLevelSequence();
		for (APlayerController* PlayerController : ConnectedPlayers)
		{
			AUserCharacter* UserCharacter = Cast<AUserCharacter>(PlayerController->GetPawn());
			UserCharacter->RemoveWidget();
		}
	}
}

void ABossGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
		ConnectedPlayers.Add(NewPlayer); 
}

void ABossGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AUserPlayerController* ExitingPlayer = Cast<AUserPlayerController>(Exiting);
	if (ExitingPlayer)
		ConnectedPlayers.Remove(ExitingPlayer);
}

void ABossGameMode::OnCinematicFinished()
{
	for (APlayerController* PlayerController : ConnectedPlayers)
	{
		AUserCharacter* UserCharacter = Cast<AUserCharacter>(PlayerController->GetPawn());
		UserCharacter->SetWidget();
	}

	for (AEnemyCharacter* Enemy : EnemyClassArray)
	{
		BossCharacter = Cast<ABossCharacter>(Enemy);
		BossCharacter->ShowHpBar();
		BossCharacter->StartAISearch();
	}
}

void ABossGameMode::SetDelegate()
{
	for (int32 i = 0; i < EnemyClassArray.Num(); i++)
	{
		if (EnemyClassArray[i]->GetClass() == ABossCharacter::StaticClass())
		{
			BossCharacter = Cast<ABossCharacter>(EnemyClassArray[i]);
			BossCharacter->StartAISearch();
			//BossCharacter->UseSkill("Golem_Ready");
			BossCharacter->OnDied.AddUObject(this, &ABossGameMode::BossDied);
			for (APlayerController* PlayerController : ConnectedPlayers)
			{
				AUserPlayerController* User = Cast<AUserPlayerController>(PlayerController);
				User->SyncEnemyHpBar(BossCharacter);
			}
		}
	}
}

void ABossGameMode::BossDied()
{
	ActivateSlowMotion(0.3f, 2.0f);
	if (PotalBP)
	{
		auto LevelPotal = GetWorld()->SpawnActor<ALevelPotal>(PotalBP, FVector(-7442.f, -5852.f, 226.f), FRotator::ZeroRotator);
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

void ABossGameMode::DelayedStart()
{
	//PlayCinematic();
	SetDelegate();
}