// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MakeCharController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API AMakeCharController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMakeCharController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BPFunction();

private:
	TSubclassOf<class UUserWidget> UW_MakeCharWidget;
	class UW_MakeCharacter* W_MakeCharacter;
};
