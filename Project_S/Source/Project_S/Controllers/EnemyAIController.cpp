// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetActorTickEnabled(true);
	CountSearch = 0;
	IsMoving = false;
	IsBackToTheHome = false;
	FirstLocation = GetPawn()->GetActorLocation();
	StartTime = GetWorld()->GetDeltaSeconds();
	EndTime = GetWorld()->GetDeltaSeconds();
	PlayTime = 1.f;
	IsDead = false;
	ChkState = E_State::E_Search;
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	SetActorTickEnabled(false);
	SetFocus(nullptr);
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

void AEnemyAIController::ResetFirst()
{
	// Reset Location , Rotator;
	SetMaxSpeed(1200.f);
	MoveToLocation(FirstLocation, 10);
	IsMoving = true;
	IsMoveAtFirst = false;
	CountSearch = 0;
	ChkState = E_State::E_Search;
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
void AEnemyAIController::SetMaxSpeed(float NewMaxSpeed)
{
	// 제어하는 Pawn이 유효한지 확인
	if (APawn* ControlledPawn = GetPawn())
	{
		// 제어하는 Pawn이 ACharacter인지 확인
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			// CharacterMovementComponent를 통해 최대 속도를 설정
			ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
		}
	}
}

