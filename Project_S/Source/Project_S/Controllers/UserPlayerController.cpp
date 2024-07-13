// Fill out your copyright notice in the Description page of Project Settings.


#include "UserPlayerController.h"
#include "Project_S/Character/UserCharacter.h"
#include "Project_S/Character/EnemyCharacter.h"

AUserPlayerController::AUserPlayerController()
{
	bShowMouseCursor = false;
}

void AUserPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	AUserCharacter* UserCharacter = Cast<AUserCharacter>(GetPawn());

	if (UserCharacter)
	{
		UserCharacter->SetUserWidget();
	}
}

void AUserPlayerController::SetUserWidget()
{
	AUserCharacter* UserCharacter = Cast<AUserCharacter>(GetPawn());

	if (UserCharacter)
	{
		UserCharacter->SetWidget();
	}
}

void AUserPlayerController::RemoveUserWidget()
{
	AUserCharacter* UserCharacter = Cast<AUserCharacter>(GetPawn());

	if (UserCharacter)
	{
		UserCharacter->RemoveWidget();
	}
}

void AUserPlayerController::SyncEnemyHpBar_Implementation(AEnemyCharacter* _Enemy)
{
	if (_Enemy)
		_Enemy->ShowHpBar();
}


void AUserPlayerController::SyncRemoveEnemyHpBar_Implementation(AEnemyCharacter* _Enemy)
{
	if (_Enemy)
	{
		_Enemy->RemoveWidget();
	}
}
