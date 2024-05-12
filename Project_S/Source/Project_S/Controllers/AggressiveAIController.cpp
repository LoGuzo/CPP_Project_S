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
}

void AAggressiveAIController::AISerach()
{

	if (CountSearch < 5)
	{
		auto CurrentPawn = GetPawn();
		if (CurrentPawn == nullptr)
			return;
		UWorld* World = CurrentPawn->GetWorld();
		FVector Center = CurrentPawn->GetActorLocation();
		float SearchRadius = 500.f;

		if (World == nullptr)
			return;

		TArray<FOverlapResult>OverlapResults;
		FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);

		bool bResult = World->OverlapMultiByChannel(
			OverlapResults,
			Center,
			FQuat::Identity,
			ECollisionChannel::ECC_EngineTraceChannel2,
			FCollisionShape::MakeSphere(SearchRadius),
			QueryParams);

		if (bResult)
		{
			for (auto& OverlapResult : OverlapResults) {
				User = Cast<AUserCharacter>(OverlapResult.GetActor());
				if (User && User->GetController()->IsPlayerController())
				{
					CountSearch = 0;
					DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
					ChkState = E_State::E_Move;
					return;
				}
			}
		}
		if (IsMoveAtFirst)
		{
			CountSearch++;
		}
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
	else {
		ChkState = E_State::E_Reset;
	}
}

void AAggressiveAIController::AIMove()
{
	if (IsMoving == true)
		return;
	MoveToActor(User);
	IsMoving = true;
	IsMoveAtFirst = true;
}

void AAggressiveAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
	if (Result.IsSuccess()) {
		IsMoving = false;
		ChkState = E_State::E_Search;
	}
}
