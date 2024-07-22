// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_ChatBalloon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_ChatBalloon : public UMainUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Txt_Bubble;
};
