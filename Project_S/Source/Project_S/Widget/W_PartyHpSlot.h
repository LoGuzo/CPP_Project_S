// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_PartyHpSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_PartyHpSlot : public UMainUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Name;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;

};
