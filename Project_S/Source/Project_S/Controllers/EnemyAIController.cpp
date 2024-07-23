// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_S/Character/UserCharacter.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetActorTickEnabled(true);

	CountSearch = 0;
	IsMoving = false;
	IsDead = false;
	IsBackToTheHome = false;

	FirstLocation = GetPawn()->GetActorLocation();

	StartTime = GetWorld()->GetDeltaSeconds();
	EndTime = GetWorld()->GetDeltaSeconds();

	PlayTime = 1.f;
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	SetActorTickEnabled(false);
	SetFocus(nullptr);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EndTime += DeltaTime;
	if (!IsBackToTheHome)
	{
		if (StartTime + PlayTime < EndTime)
		{
			if(!IsDead)
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
	if (APawn* ControlledPawn = GetPawn())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
			ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
	}
}

void AEnemyAIController::StartAISearch()
{
	ChkState = E_State::E_Search;
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
	if (Result.IsSuccess()) {
		IsMoving = false;
	}
}

void AEnemyAIController::LookAtPlayer(const FVector& TargetLocation)
{
	FVector PlayerLocation = TargetLocation;
	FVector AILocation = GetPawn()->GetActorLocation();
	FVector Direction = (PlayerLocation - AILocation).GetSafeNormal();

	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAtRotation.Pitch = 0.0f;
	LookAtRotation.Roll = 0.0f;

	GetPawn()->SetActorRotation(LookAtRotation);

	SetControlRotation(LookAtRotation);
}

