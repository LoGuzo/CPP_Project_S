// Fill out your copyright notice in the Description page of Project Settings.


#include "AggressiveAIController.h"
#include "DrawDebugHelpers.h"
#include "Project_S/Character/UserCharacter.h"
void AAggressiveAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AAggressiveAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAggressiveAIController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AAggressiveAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SDistance(FirstLocation, GetPawn()->GetActorLocation()) > 1000.f)
	{
		ChkState = E_State::E_Reset;
	}
}

void AAggressiveAIController::AISerach()
{
	SetMaxSpeed(150.f);
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
				CountSearch = 0;
				IsMoveAtFirst = false;
				DrawDebugSphere(World, Center, SearchRadius, 10, FColor::Green, false, 0.2f);
				ChkState = E_State::E_Move;
				return;
			}
		}
	}
	if (IsMoveAtFirst)
	{
		CountSearch++;
		if (CountSearch > 4)
		{
			ChkState = E_State::E_Reset;
			return;
		}
	}
	DrawDebugSphere(World, Center, SearchRadius, 10, FColor::Red, false, 0.2f);

}

void AAggressiveAIController::Attack()
{
	
}

void AAggressiveAIController::AIMove()
{
	if (IsMoving == true)
		return;
	SetMaxSpeed(600.f);
	IsMoving = true;
	IsMoveAtFirst = true;
	MoveToActor(User);
}

void AAggressiveAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
	if (Result.IsSuccess()) {
		IsMoving = false;
		ChkState = E_State::E_Search;
	}
}