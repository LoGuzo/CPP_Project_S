// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SInBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API USInBase : public UGameInstance
{
	GENERATED_BODY()

public:
	USInBase();
	
	virtual void Init() override;

private:
	class UCharacterManager* CharManage;
};
