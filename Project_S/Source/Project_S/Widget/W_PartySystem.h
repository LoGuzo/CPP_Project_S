// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_PartySystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_PartySystem : public UMainUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Make;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Add;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* Box_Slot;
};
