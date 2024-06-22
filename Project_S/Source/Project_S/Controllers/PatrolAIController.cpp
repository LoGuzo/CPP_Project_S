// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolAIController.h"

/*void APatrolAIController::AISerach()
{
	if (IsMoving == true)
		return;
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
}*/