// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include <Kismet/GameplayStatics.h>

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	/*StartTime = GetWorld()->GetDeltaSeconds();
	EndTime = GetWorld()->GetDeltaSeconds();
	PlayTime = 1.f;*/
	Location.Emplace(MakeShared<FVector>(FVector(-20.f, -620.f, 498.f)));
	Location.Emplace(MakeShared<FVector>(FVector(-780.f, -430.f, 218.f)));

	for (int i = 0; i < Location.Num(); i++)
	{
		WeakLocation.Emplace(Location[i]);
	}
	MoveToLocation(*WeakLocation[0].Pin(), 100);
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

	/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	EndTime += DeltaTime;
	if (StartTime + PlayTime < EndTime)
	{
		//FSMState();

		EndTime = 0;
		StartTime = GetWorld()->GetDeltaSeconds();
	}*/
	//SetFocus(PlayerPawn);
	//MoveToActor(PlayerPawn, 100);
	//MoveToLocation(*WeakLocation[0].Pin(), 100);
	if (MoveToLocation(*WeakLocation[0].Pin(), 100))
	{
		UE_LOG(LogTemp, Warning, TEXT("True"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("False"));
	}
}
void AEnemyAIController::Attack()
{
	//EnemyAttack
}
void AEnemyAIController::ResetFirst()
{
	// Reset Location , Rotator;
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
		MoveToLocation(*WeakLocation[0].Pin(), 100);
		break;
	}
}


