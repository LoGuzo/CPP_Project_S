// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerController.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ALobbyController : public AMainPlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> ULobby_Widget;
	class UW_CharacterLobby* W_CharacterLobby;
};
