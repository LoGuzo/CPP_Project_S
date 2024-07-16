// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_PartySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_PartySlot : public UMainUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Lvl;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Leader;
};
