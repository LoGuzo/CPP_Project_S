// Fill out your copyright notice in the Description page of Project Settings.


#include "W_QuestSystem.h"
#include "W_QuestSlot.h"
#include "Components/WrapBox.h"

UW_QuestSystem::UW_QuestSystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UW_QuestSlot>UW(TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/Blueprints/Widget/WBp_QuestSlot.WBP_QuestSlot_C'"));
	if (UW.Succeeded())
		TW_QuestSlot = UW.Class;
}

void UW_QuestSystem::UpdateSlots(const TArray<FQuestNode*>& Slots)
{
	Wrap_Quest->ClearChildren();
	for (const FQuestNode* slot : Slots)
	{
		if (slot)
		{
			W_QuestSlot = CreateWidget<UW_QuestSlot>(GetWorld(), TW_QuestSlot);
			if (W_QuestSlot)
			{
				W_QuestSlot->SetQuestContent(slot->QuestInfo->Description);
				W_QuestSlot->SetCurrentValue(slot->CurrentValue);
				W_QuestSlot->SetClearValue(slot->QuestData->ClearValue);
			}
			Wrap_Quest->AddChild(W_QuestSlot);
		}
	}
}