// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "W_QuestSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_QuestSlot : public UMainUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Content;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Cnt;

	FText QuestContent;

	int32 CurrentValue;

	int32 ClearValue;

public:
	void SetQuestContent(FText _QuestContent);
	FText GetQuestContent() { return QuestContent; }

	void SetCurrentValue(int32 _CurrentValue);
	int32 GetCurrentValue() { return CurrentValue; }

	void SetClearValue(int32 _ClearValue);
	int32 GetClearValue() { return ClearValue; }
};
