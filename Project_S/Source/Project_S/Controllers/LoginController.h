// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginController.generated.h"

/**
 * 
 */
struct FUserID;

UCLASS()
class PROJECT_S_API ALoginController : public APlayerController
{
	GENERATED_BODY()

public:
	ALoginController();

	void LoginSuccessful(const FUserID& UserData);

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> ULogin_Widget;
	class UW_Login* W_Login;
};
