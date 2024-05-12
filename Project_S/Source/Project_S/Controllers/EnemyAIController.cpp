// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Project_S/Character/EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	ChkState = E_State::E_Search;
	CountSearch = 0;
	IsMoving = false;
	IsBackToTheHome = false;
	FirstLocation = GetPawn()->GetActorLocation();
	StartTime = GetWorld()->GetDeltaSeconds();
	EndTime = GetWorld()->GetDeltaSeconds();
	PlayTime = 3.f;
}

void AEnemyAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Location.Num() != 0)
	{
		Location.Reset();
	}
	if (WeakLocation.Num() != 0)
	{
		WeakLocation.Reset();
	}
}

void AEnemyAIController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EndTime += DeltaTime;
	if (!IsBackToTheHome)
	{
		if (StartTime + PlayTime < EndTime)
		{
			FSMState();

			EndTime = 0;
			StartTime = GetWorld()->GetDeltaSeconds();
		}
	}
}
void AEnemyAIController::Attack()
{
	//EnemyAttack
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetOwner());
	if(Enemy)
	{
	//Enemy->Attack();
	}
}
void AEnemyAIController::ResetFirst()
{
	// Reset Location , Rotator;
	MoveToLocation(FirstLocation, 10);
	IsMoving = true;
	IsMoveAtFirst = false;
	CountSearch = 0;
}
void AEnemyAIController::FSMState()
{
	switch (ChkState)
	{
	case E_State::E_Search:
		AISerach();
		break;
	case E_State::E_Move:
		AIMove();
		break;
	case E_State::E_Attack:
		Attack();
		break;
	case E_State::E_Reset:
		ResetFirst();
		break;
	default:
		break;
	}
}


