// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_SGameMode.h"
#include "BossGameMode.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT_S_API ABossGameMode : public AProject_SGameMode
{
	GENERATED_BODY()

public:
	ABossGameMode();

	virtual void MonsterFactory() override;
};
