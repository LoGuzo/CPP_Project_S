// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarAIController.h"
#include "GameFramework/Character.h"
#include "Project_S/PathFinder.h"


AAStarAIController::AAStarAIController()
{
	PathFinder = CreateDefaultSubobject<APathFinder>(TEXT("Pathfinder"));
}

void AAStarAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PathIndex = 0;
	DetailPathIndex = 0;

	ChkState = E_State::E_Move;
	WalkStop = NowState::E_Stop;
}

void AAStarAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Location.Num() != 0)
		Location.Reset();
}

void AAStarAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (WalkStop == NowState::E_Walk)
		MoveFoward(DeltaSeconds);
}

void AAStarAIController::AIMove()
{
	SetMaxSpeed(150.f);
	MoveToNextPatrolPoint();
}

void AAStarAIController::MoveToNextPatrolPoint()
{
	if (Location.Num() == 0) return;

	if (SDistance(Location[PathIndex], GetPawn()->GetActorLocation()) < 100.f)
	{
		DetailPath.Empty();
		WalkStop = NowState::E_Stop;
		PathIndex = (PathIndex + 1) % Location.Num();
	}

	MoveToLocationUsingAStar(Location[PathIndex]);
}

void AAStarAIController::MoveToLocationUsingAStar(const FVector& TargetLocation)
{
	if (DetailPath.Num() == 0)
	{
		DetailPathIndex = 0;
		if (!PathFinder->FindPath(GetPawn()->GetActorLocation(), TargetLocation, DetailPath)) return;
	}

	WalkStop = NowState::E_Walk;

	if (SDistance(DetailPath[DetailPathIndex], GetPawn()->GetActorLocation()) < 100.f)
		DetailPathIndex = (DetailPathIndex + 1) % DetailPath.Num();

	LookAtPlayer(DetailPath[DetailPathIndex]);
}

void AAStarAIController::MoveFoward(float DeltaTime)
{
	ACharacter* MyCharacter = Cast<ACharacter>(GetPawn());
	MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector(), 150.f * DeltaTime);
}

void AAStarAIController::SetLocation(const TArray<FVector>& _Location)
{
	Location = _Location;
}


