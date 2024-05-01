// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameManagerBase.h"

/**
 * 
 */
class PROJECT_S_API SkillManager : public SGameManagerBase
{
public:

	SkillManager();

	virtual FSkillTable* GetMyData(FString _Init) override;
};
