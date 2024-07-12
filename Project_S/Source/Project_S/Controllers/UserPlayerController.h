// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UserPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AUserPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUserPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Client, Reliable)
	void SyncEnemyHpBar(class AEnemyCharacter* _Enemy);
};
