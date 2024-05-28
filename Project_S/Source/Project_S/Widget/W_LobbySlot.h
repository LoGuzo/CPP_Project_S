// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_LobbySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_LobbySlot : public UMainUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Char;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Char;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Create;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Box_Info;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Lvl;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Class;
};
