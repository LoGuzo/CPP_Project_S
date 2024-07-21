// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainUserWidget.h"
#include "Project_S/S_StructureAll.h"
#include "W_QuestSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_S_API UW_QuestSystem : public UMainUserWidget
{
	GENERATED_BODY()

public:
	UW_QuestSystem(const FObjectInitializer& ObjectInitializer);

	void UpdateSlots(const TArray<FQuestNode*>& Slots);
private:
	TSubclassOf<class UW_QuestSlot> TW_QuestSlot;
	class UW_QuestSlot* W_QuestSlot;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* Wrap_Quest;
};
