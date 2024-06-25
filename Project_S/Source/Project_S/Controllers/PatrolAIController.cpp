// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolAIController.h"
#include "DrawDebugHelpers.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/FirstCharacter.h"
#include "Project_S/Component/C_SkillComponent.h"

void APatrolAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PathIndex = 0;
	IsFindEnemy = false;
	ChkState = E_State::E_Search;
}

void APatrolAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void APatrolAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Location.Num() != 0)
	{
		Location.Reset();
	}
}

void APatrolAIController::AISerach()
{
	auto CurrentPawn = GetPawn();
	if (CurrentPawn == nullptr)
		return;
	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;

	if (World == nullptr)
		return;
	TArray<FHitResult>HItResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);
	bool bResult = World->SweepMultiByChannel(
		HItResults,
		Center,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams);

	if (bResult)
	{
		for (auto& HItResult : HItResults) {
			User = Cast<AUserCharacter>(HItResult.GetActor());
			if (User && User->GetController()->IsPlayerController())
			{
				SetMaxSpeed(600.f);
				DrawDebugSphere(World, Center, SearchRadius, 10, FColor::Green, false, 0.2f);
				MoveToActor(User);
				ChkState = E_State::E_Attack;
				return;
			}
		}
	}
	SetMaxSpeed(150.f);
	DrawDebugSphere(World, Center, SearchRadius, 10, FColor::Red, false, 0.2f);
	ChkState = E_State::E_Move;
}

void APatrolAIController::AIMove()
{
	MoveToNextPatrolPoint();
	ChkState = E_State::E_Search;
}

void APatrolAIController::Attack()
{
	if (IsMoving == true)
		return;
	if (User && !IsDead)
	{
		LookAtPlayer();
		if (SDistance(User->GetActorLocation(), GetPawn()->GetActorLocation()) <= 200.f)
		{
			const auto Enemy = Cast<AFirstCharacter>(GetPawn());
			if (Enemy) {
				Enemy->UseSkill(Enemy->GetSkillCom()->GetSlot(0).ItemName.ToString());
				return;
			}
		}
	}
	ChkState = E_State::E_Search;
}

void APatrolAIController::MoveToNextPatrolPoint()
{
	if (Location.Num() == 0)
	{
		return;
	}
	MoveToLocation(Location[PathIndex]);
	IsMoving = true;
	if (SDistance(Location[PathIndex], GetPawn()->GetActorLocation()) < 50.f)
	{
		PathIndex = (PathIndex + 1) % Location.Num();
	}
}

void APatrolAIController::SetLocation(TArray<FVector> _Location)
{
	Location = _Location;
}

