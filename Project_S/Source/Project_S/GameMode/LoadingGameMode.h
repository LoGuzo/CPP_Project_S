// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoadingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API ALoadingGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALoadingGameMode();

protected:
	virtual void BeginPlay() override;

	
private:
	TSubclassOf<UUserWidget> W_LoadingScene;
	class UMainUserWidget* LoadingScene;

	void NextLevel();

	UFUNCTION()
	void OnLevelLoaded();
};
