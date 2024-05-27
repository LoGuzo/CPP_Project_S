// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ALoginController : public APlayerController
{
	GENERATED_BODY()

public:
	ALoginController();

	void LoginSuccessful(const FString& Username);

	FString GetPlayerUsername() const { return PlayerUsername; }
protected:
	virtual void BeginPlay() override;

private:
	FString PlayerUsername;

	TSubclassOf<class UUserWidget> ULogin_Widget;
	class UW_Login* W_Login;
};
