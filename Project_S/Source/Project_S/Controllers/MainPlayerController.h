// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	void SendMessage(const FText& Text);

	UFUNCTION()
	void FocusChatInputText();

	UFUNCTION()
	void FocusGame();

private:
	UFUNCTION(Server, Unreliable)
	void Server_SendMessage(const FString& Message);
	UFUNCTION(Client, Unreliable)
	void Client_SendMessage(const FString& Message);
};
