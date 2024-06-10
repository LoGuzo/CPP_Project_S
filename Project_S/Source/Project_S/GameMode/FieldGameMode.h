// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_SGameMode.h"
#include "FieldGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AFieldGameMode : public AProject_SGameMode
{
	GENERATED_BODY()
	
public:
	AFieldGameMode();

	virtual void MonsterFactory() override;
};
