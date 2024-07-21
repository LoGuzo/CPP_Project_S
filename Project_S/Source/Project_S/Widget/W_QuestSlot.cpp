// Fill out your copyright notice in the Description page of Project Settings.


#include "W_QuestSlot.h"
#include "Components/TextBlock.h"

void UW_QuestSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Txt_Content)
		Txt_Content->SetText(QuestContent);

	if (Txt_Cnt)
	{
		FText CntText = FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentValue, ClearValue));
		Txt_Cnt->SetText(CntText);
	}
}

void UW_QuestSlot::SetQuestContent(FText _QuestContent)
{
	QuestContent = _QuestContent;
}

void UW_QuestSlot::SetCurrentValue(int32 _CurrentValue)
{
	CurrentValue = _CurrentValue;
}

void UW_QuestSlot::SetClearValue(int32 _ClearValue)
{
	ClearValue = _ClearValue;
}