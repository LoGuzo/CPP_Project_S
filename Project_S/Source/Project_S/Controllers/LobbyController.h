// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ALobbyController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyController();

protected:
	virtual void BeginPlay() override;

};
